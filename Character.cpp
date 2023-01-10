#include "menus/buttons.hpp"
#include "DBM.h"
#include "Arena.hpp"
#include <random>
#include <ctime>

using namespace easyGUI;

std::vector<Item> inventory;
std::map<std::string, int> modifiers;
int monsterID = 0;
int nextInOrder = 0;
std::string phase = "Setup";

std::vector<std::pair<std::string, int>> order;
std::map<std::string, int> monsters;

void sell_item_action()
{
	easyGUI::Application* app = nullptr;

	app = app->getInstance();

	if (app != nullptr)
	{
		int index = std::stoi(item);
	
		if (inventory[index].quantity <= 0) {
			return;
		}

		std::shared_ptr<DBM> inst = DBM::getInstance("127.0.0.1", "3306", "vap_pi", "root", "En3RgYm4x0u7");
		std::map<std::string, std::string> filter;
		sql::ResultSet* res = inst->runQuery(DBM::QueryType::SELECT, "players", "Gold", filter);
		if (res->next()) {
			cost = res->getInt("Gold");
			delete res;
		}
		res = inst->runQuery(DBM::QueryType::UPDATE, "players", "Gold=" + std::to_string(cost+inventory[index].price), filter);

		filter["ID"] = inventory[index].ID;

		std::cout << index;
		inventory[index].quantity--;

		if (inventory[index].quantity != 0)
			res = inst->runQuery(DBM::QueryType::UPDATE, "inventory", "Quantity=" + std::to_string(inventory[index].quantity), filter);
		else
			res = inst->runQuery(DBM::QueryType::DELETE, "inventory", "", filter);

		{
			std::wstring wstr(L"Stock: ");
			std::wstring buffer;

			StringToWString(buffer, std::to_string(inventory[index].quantity));
			wstr.append(buffer);

			easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("item" + item + "stock"))->getInternalText().setString(sf::String(wstr));
		}
	}
}

void generate_inventory()
{
	std::shared_ptr<DBM> inst = DBM::getInstance("127.0.0.1", "3306", "vap_pi", "root", "En3RgYm4x0u7");

	std::map<std::string, std::string> filter;
	sql::ResultSet* res = inst->runQuery(DBM::QueryType::SELECT, "inventory", "*", filter);
	inventory.clear();
	modifiers.clear();

	while (res->next()) {
		Item item;
		item.bought = 0;
		item.quantity = res->getInt("Quantity");
		item.ID = res->getString("ID");

		filter["ID"] = res->getString("Item");
		sql::ResultSet* res2 = inst->runQuery(DBM::QueryType::SELECT, "items", "Name, Rarity, (SELECT Name from stats WHERE ID=Stat) AS \"Stat\", Value", filter);

		if (res2->next()) {
			item.Name = res2->getString("Name");
			modifiers[res2->getString("Stat")] = res2->getInt("Value");

			std::map<std::string, std::string> filter2;
			filter2["ID"] = res2->getString("Rarity");

			sql::ResultSet* res3 = inst->runQuery(DBM::QueryType::SELECT, "rarities", "LowPrice, HighPrice", filter2);
			if (res3->next()) {
				std::random_device rd; // obtain a random number from hardware
				std::mt19937 gen(rd()); // seed the generator
				std::uniform_int_distribution<> distr2(res3->getInt("LowPrice"), res3->getInt("HighPrice"));
				item.price = distr2(gen);

				delete res3;
			}

			delete res2;
		}

		inventory.push_back(item);
	}

	delete res;
}

void items_action()
{
	Application* app = nullptr;
	app = app->getInstance();
	Menu* menu = nullptr;

	if (app->getMenu("itemView1234"))
	{
		menu = app->getMenu("itemView1234");
		menu->clear();
	}
	else
	{
		menu = app->addMenu("itemView1234");
	}

	unsigned factor = 0;
	for (const Item& item : inventory)
	{
		AddElement(menu, new Label(Point(50, 150 + 50 * factor), item.Name, "./res/Arial.ttf", 25), "item" + std::to_string(factor) + "title");

		AddElement(menu, new Button(Point(50, 185 + 50 * factor), Point(700, 186 + 50 * factor), "", "./res/Arial.ttf", 0), "Line" + std::to_string(factor));
		Converter::getButton(menu->getComponent("Line" + std::to_string(factor)))->getInternalButton().setFillColor(sf::Color::White);
		Converter::getButton(menu->getComponent("Line" + std::to_string(factor)))->getInternalButton().setOutlineThickness(1);

		AddElement(menu, new Label(Point(180, 160 + 50 * factor), "Stock: " + std::to_string(item.quantity), "./res/Arial.ttf", 15), "item" + std::to_string(factor) + "stock");
		AddElement(menu, new Label(Point(280, 160 + 50 * factor), "Price: " + std::to_string(item.price), "./res/Arial.ttf", 15), "item" + std::to_string(factor) + "price");

		AddElement(menu, new ItemFactory(Point(600, 150 + 50 * factor), Point(630, 180 + 50 * factor), "./res/view.png", std::to_string(factor)), "itemPlus" + std::to_string(factor));
		AddElement(menu, new ItemFactory(Point(643, 153 + 50 * factor), Point(667, 177 + 50 * factor), "./res/minus.png", std::to_string(factor)), "itemMinus" + std::to_string(factor));

		menu->getComponent("itemPlus" + std::to_string(factor))->setOnClickAction(view_item_button);
		menu->getComponent("itemMinus" + std::to_string(factor))->setOnClickAction(sell_item_action);

		factor++;
	}

	AddElement(menu, new Label(Point(350, 50), "Items", "./res/Arial.ttf", 35), "title");
	AddElement(menu, new Button(Point(250, 450), Point(500, 500), "Back", "./res/Arial.ttf", 25), "backBtn");
	menu->getComponent("backBtn")->setOnClickAction(backButton_action);

	traveresedMenus.push_back("character1234");
	app->setActiveMenu("itemView1234");
}

void remove_monster()
{
	monsters.erase(enemies.at(monsterID).name);

	int index = 0;
	for (std::pair<std::string, int>& item : order) {
		if (item.first == enemies.at(monsterID).name)
			break;
		index++;
	}

	order.erase(order.begin() + index);
	Application* app = nullptr;
	app = app->getInstance();
	Menu* menu = app->getActiveMenu();

	std::string s = "remove_btn" + std::to_string(monsterID);
	menu->removeComponent(s);
	s = "image" + std::to_string(monsterID);
	menu->removeComponent(s);

	if (monsters.empty())
		backButton_action();
}

void next_action()
{
	Application* app = nullptr;
	app = app->getInstance();
	Menu* menu = app->getActiveMenu();

	std::string s("displayImage");
	if (menu->getComponent("displayImage"))
		menu->removeComponent(s);

	if (nextInOrder == enemies.size() && phase == "Setup") {
		phase = "Combat";
		Converter::getLabel(menu->getComponent("title"))->getInternalText().setString("Combat");
		nextInOrder = 0;
	}
	else if (phase == "Setup") {
		std::string text = enemies.at(nextInOrder).name + "\n" + "-------------\nNormal enemies : " + std::to_string(enemies.at(nextInOrder).monsters) + "\nStrong enemies: " + std::to_string(enemies.at(nextInOrder).strongMonsters);
		Converter::getLabel(menu->getComponent("passive"))->getInternalText().setString(sf::String(text));
		
		AddElement(menu, new Image(Point(400, 100), Point(600, 300), enemies[nextInOrder].imagePath), "displayImage");
		enemies[nextInOrder].generateDeck();

		nextInOrder++;
	}
	
	if (phase == "Combat") {
		if (nextInOrder >= order.size())
			nextInOrder = 0;

		if (order[nextInOrder].first.find("Player") != std::string::npos) {
			Converter::getLabel(menu->getComponent("passive"))->getInternalText().setString(sf::String(order[nextInOrder].first));
			AddElement(menu, new Image(Point(400, 100), Point(600, 300), "./res/character.png"), "displayImage");
		}
		else {
			Card c = enemies[monsters[order[nextInOrder].first]].drawCard();
			std::cout << c.refresh << "\n";

			std::string str = passives[c.passiveIndex];
			str += "\n\n\n";
			str += actives[c.activeIndex];

			Converter::getLabel(menu->getComponent("passive"))->getInternalText().setString(sf::String(str));
			AddElement(menu, new Image(Point(400, 100), Point(600, 300), enemies[monsters[order[nextInOrder].first]].imagePath), "displayImage");
		}

		nextInOrder++;
	}
}

void start_btn_action()
{
	Application* app = nullptr;
	app = app->getInstance();
	Menu* menu = app->getActiveMenu();

	phase = "Setup";
	nextInOrder = 0;
	monsterID = 0;
	order.clear();
	monsters.clear();

	enemies.clear();
	int total = 0;

	if (dynamic_cast<MyCheckBox*>(menu->getComponent("box1"))->checked)
	{
		MonsterGroup group;
		
		if (players <= 2)
			group.monsters = 4;
		else if (players == 3)
			group.monsters = 6;
		else
			group.monsters = 8;

		group.name = "Goblins";
		group.imagePath = "./res/goblin-removebg-preview.png";
		group.initiative = 0;
		enemies.push_back(group);

		total++;
	}

	if (dynamic_cast<MyCheckBox*>(menu->getComponent("box2"))->checked)
	{
		MonsterGroup group;

		if (players <= 2)
			group.monsters = 3;
		else if (players == 3)
			group.monsters = 4;
		else
			group.monsters = 5;

		group.name = "Centaurs";
		group.imagePath = "./res/centaur-removebg-preview.png";
		group.initiative = 0;
		enemies.push_back(group);

		total++;
	}

	if (dynamic_cast<MyCheckBox*>(menu->getComponent("box3"))->checked)
	{
		MonsterGroup group;

		if (players <= 2)
			group.monsters = 1;
		else if (players == 3)
			group.monsters = 2;
		else
			group.monsters = 3;

		group.name = "Ettins";
		group.imagePath = "./res/ettin-removebg-preview.png";
		group.initiative = 0;
		enemies.push_back(group);

		total++;
	}

	if (dynamic_cast<MyCheckBox*>(menu->getComponent("box4"))->checked)
	{
		MonsterGroup group;

		if (players <= 2)
			group.monsters = 1;
		else if (players == 3)
			group.strongMonsters = 1;
		else
			group.monsters = 1;

		group.name = "Dragons";
		group.imagePath = "./res/dragon-removebg-preview.png";
		group.initiative = 0;
		enemies.push_back(group);

		total++;
	}

	if (dynamic_cast<MyCheckBox*>(menu->getComponent("box5"))->checked)
	{
		MonsterGroup group;

		if (players <= 2)
			group.monsters = 2;
		else if (players == 3) {
			group.strongMonsters = 1;
			group.monsters = 1;
		}
		else
			group.strongMonsters = 2;

		group.name = "Golems";
		group.imagePath = "./res/golem-removebg-preview.png";
		group.initiative = 0;
		enemies.push_back(group);

		total++;
	}

	if (dynamic_cast<MyCheckBox*>(menu->getComponent("box6"))->checked)
	{
		MonsterGroup group;

		if (players <= 2)
			group.monsters = 3;
		else if (players == 3)
			group.strongMonsters = 5;
		else
			group.monsters = 7;

		group.name = "Harpies";
		group.imagePath = "./res/harpy-removebg-preview.png";
		group.initiative = 0;
		enemies.push_back(group);

		total++;
	}

	if (total >= 1) {
		order.clear();
		monsters.clear();

		menu = nullptr;

		if (app->getMenu("battle1234"))
		{
			menu = app->getMenu("battle1234");
			menu->clear();
		}
		else
		{
			menu = app->addMenu("battle1234");
		}

		AddElement(menu, new Label(Point(50, 40), "Setup", "./res/Arial.ttf", 35), "title");

		/// BEGIN COMBAT ORDER
		int index = 0;
		for (MonsterGroup& group : enemies) {
			std::srand(unsigned(std::time(0)));

			order.push_back(std::make_pair(group.name, std::rand() % 10));
			monsters[group.name] = index;
			index++;
		}

		for (int i = 0; i < players; i++) {
			std::string name = "Player " + std::to_string(i);
			std::srand(unsigned(std::time(0)));

			order.push_back(std::make_pair(name, std::rand() % 10));
		}

		std::sort(order.begin(), order.end(), [](std::pair<std::string, int> x, std::pair<std::string, int> y) {return x.second > y.second; });
		/// END COMBAT ORDER

		// Create monster cards
		index = 0;
		for (MonsterGroup& group : enemies) {
			AddElement(menu, new MonsterFactory(Point(620, 130 + 120 * index), "X", "./res/Arial.ttf", 35, index), "remove_btn" + std::to_string(index));
			menu->getComponent("remove_btn" + std::to_string(index))->setOnClickAction(remove_monster);

			AddElement(menu, new Image(Point(650, 100 + 120 * index), Point(750, 200 + 120 * index), group.imagePath), "image" + std::to_string(index));
			//AddElement(menu, new MyCheckBox(Point(560, 190), Point(580, 210)), "box1");
			index++;
		}

		// Creating central area
		AddElement(menu, new Border(Point(50, 100), Point(600, 500)), "central");
		AddElement(menu, new Border(Point(400, 100), Point(600, 300)), "central_image");

		AddElement(menu, new Label(Point(60, 110), "aaaa", "./res/Arial.ttf", 25), "passive");
		
		AddElement(menu, new Button(Point(150, 530), Point(300, 580), "Back", "./res/Arial.ttf", 25), "back_btn");
		AddElement(menu, new Button(Point(350, 530), Point(500, 580), "Next", "./res/Arial.ttf", 25), "next_btn");

		menu->getComponent("back_btn")->setOnClickAction(backButton_action);
		menu->getComponent("next_btn")->setOnClickAction(next_action);

		// Perform setup

		traveresedMenus.push_back("arena1234");
		app->setActiveMenu("battle1234");
	
		next_action();
	}
}

void arena_action()
{
	Application* app = nullptr;
	app = app->getInstance();
	Menu* menu = nullptr;

	if (app->getMenu("arena1234"))
	{
		menu = app->getMenu("arena1234");
		menu->clear();
	}
	else
	{
		menu = app->addMenu("arena1234");
	}

	players = 1;

	AddElement(menu, new Label(Point(300, 50), "Setup arena", "./res/Arial.ttf", 35), "title");
	AddElement(menu, new Button(Point(50, 100), Point(700, 101), "", "./res/Arial.ttf", 0), "Line1");
	Converter::getButton(menu->getComponent("Line1"))->getInternalButton().setFillColor(sf::Color::White);
	Converter::getButton(menu->getComponent("Line1"))->getInternalButton().setOutlineThickness(1);

	AddElement(menu, new Label(Point(50, 120), "Players: 1", "./res/Arial.ttf", 25), "Players");
	AddElement(menu, new Image(Point(180, 120), Point(210, 150), "./res/plus.png"), "playersPlus");
	AddElement(menu, new Image(Point(223, 123), Point(247, 147), "./res/minus.png"), "playersMinus");

	AddElement(menu, new Button(Point(50, 300), Point(250, 350), "Start", "./res/Arial.ttf", 25), "startBtn");
	AddElement(menu, new Button(Point(50, 400), Point(250, 450), "Back", "./res/Arial.ttf", 25), "backBtn");

	menu->getComponent("playersPlus")->setOnClickAction(add_players_action);
	menu->getComponent("playersMinus")->setOnClickAction(remove_players_action);
	menu->getComponent("backBtn")->setOnClickAction(backButton_action);
	menu->getComponent("startBtn")->setOnClickAction(start_btn_action);

	AddElement(menu, new Border(Point(600, 150), Point(700, 250)), "border1");
	AddElement(menu, new Image(Point(600, 150), Point(700, 250), "./res/goblin-removebg-preview.png"), "goblins");
	AddElement(menu, new MyCheckBox(Point(560, 190), Point(580, 210)), "box1");

	AddElement(menu, new Border(Point(600, 300), Point(700, 400)), "border2");
	AddElement(menu, new Image(Point(600, 300), Point(700, 400), "./res/centaur-removebg-preview.png"), "centaur");
	AddElement(menu, new MyCheckBox(Point(560, 340), Point(580, 360)), "box2");

	AddElement(menu, new Border(Point(600, 450), Point(700, 550)), "border3");
	AddElement(menu, new Image(Point(600, 450), Point(700, 550), "./res/ettin-removebg-preview.png"), "ettin");
	AddElement(menu, new MyCheckBox(Point(560, 490), Point(580, 510)), "box3");

	AddElement(menu, new Border(Point(400, 150), Point(500, 250)), "border4");
	AddElement(menu, new Image(Point(400, 150), Point(500, 250), "./res/dragon-removebg-preview.png"), "dragon");
	AddElement(menu, new MyCheckBox(Point(360, 190), Point(380, 210)), "box4");

	AddElement(menu, new Border(Point(400, 300), Point(500, 400)), "border5");
	AddElement(menu, new Image(Point(400, 300), Point(500, 400), "./res/golem-removebg-preview.png"), "golem");
	AddElement(menu, new MyCheckBox(Point(360, 340), Point(380, 360)), "box5");

	AddElement(menu, new Border(Point(400, 450), Point(500, 550)), "border6");
	AddElement(menu, new Image(Point(400, 450), Point(500, 550), "./res/harpy-removebg-preview.png"), "harpy");
	AddElement(menu, new MyCheckBox(Point(360, 490), Point(380, 510)), "box6");

	traveresedMenus.push_back("character1234");
	app->setActiveMenu("arena1234");
}

void create_character_menu(easyGUI::Application* app)
{
	if (!app)
		throw easyGUI::MenuException("Couldn't create menu.");

	easyGUI::Menu* menu;
	if (app->getMenu("character1234"))
	{
		menu = app->getMenu("character1234");
		menu->clear();
	}
	else
	{
		menu = app->addMenu("character1234");
	}

	generate_inventory();
	std::shared_ptr<DBM> inst = DBM::getInstance("127.0.0.1", "3306", "vap_pi", "root", "En3RgYm4x0u7");

	std::map<std::string, std::string> filter;
	sql::ResultSet* res = inst->runQuery(DBM::QueryType::SELECT, "modifiers", "(SELECT Name FROM stats WHERE ID = modifiers.Modifier) AS \"Stat\", Value", filter);

	int i = 0;
	int j = 0;

	while (res->next())
	{
		int val = res->getInt("Value") + modifiers[res->getString("Stat")];
		std::string text = res->getString("Stat") + " : " + std::to_string(val);
		
		if (res->getString("Stat") != "HP" && res->getString("Stat") != "Armor") {
			AddElement(menu, new Label(Point(230 + 150 * (i % 3), 120 + 50 * (i / 3)), text, "./res/Arial.ttf", 25), "Stat" + std::to_string(i));
		}
		else {
			AddElement(menu, new Label(Point(70, 230 + 40 * j), text, "./res/Arial.ttf", 25), "Stat" + std::to_string(i));
			j++;
		}

		i++;
	}

	delete res;
	res = inst->runQuery(DBM::QueryType::SELECT, "players", "Gold", filter);
	
	if (res->next()) {
		AddElement(menu, new Label(Point(70, 230 + 40 * j), "Gold: " + res->getString("Gold"), "./res/Arial.ttf", 25), "Stat" + std::to_string(i));
	}
	delete res;

	AddElement(menu, new Label(Point(270, 50), "Character Data", "./res/Arial.ttf", 35), "title");
	AddElement(menu, new Button(Point(50, 100), Point(700, 101), "", "./res/Arial.ttf", 0), "Line1");
	Converter::getButton(menu->getComponent("Line1"))->getInternalButton().setFillColor(sf::Color::White);
	Converter::getButton(menu->getComponent("Line1"))->getInternalButton().setOutlineThickness(1);

	AddElement(menu, new Image(Point(70, 120), Point(170, 220), "./res/character.png"), "imag");
	AddElement(menu, new Button(Point(200, 100), Point(201, 500), "", "./res/Arial.ttf", 0), "Line2");
	Converter::getButton(menu->getComponent("Line2"))->getInternalButton().setFillColor(sf::Color::White);
	Converter::getButton(menu->getComponent("Line2"))->getInternalButton().setOutlineThickness(1);

	AddElement(menu, new Button(Point(70, 400), Point(170, 450), "Back", "./res/Arial.ttf", 25), "backBtn");

	AddElement(menu, new Button(Point(360, 250), Point(510, 300), "Items", "./res/Arial.ttf", 25), "itemsBtn");
	AddElement(menu, new Button(Point(360, 350), Point(510, 400), "Shop", "./res/Arial.ttf", 25), "shopBtn");
	AddElement(menu, new Button(Point(360, 450), Point(510, 500), "Arena", "./res/Arial.ttf", 25), "arenaBtn");

	menu->getComponent("backBtn")->setOnClickAction(backButton_action);
	menu->getComponent("shopBtn")->setOnClickAction(charsButton_action);
	menu->getComponent("arenaBtn")->setOnClickAction(arena_action);
	menu->getComponent("itemsBtn")->setOnClickAction(items_action);
}