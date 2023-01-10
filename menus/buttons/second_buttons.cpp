#include "../buttons.hpp"
#include "../../DBM.h"

using namespace easyGUI;

int cost = 0;

void db_update()
{
    // Get worlds from DB
    std::shared_ptr<DBM> inst = DBM::getInstance("127.0.0.1", "3306", "vap_pi", "root", "En3RgYm4x0u7");

    if (!inst)
        throw MenuException("Could not connect to database.");

    std::map<std::string, std::string> filter;
    filter["ID"] = "1";

    sql::ResultSet* res = inst->runQuery(DBM::QueryType::UPDATE, "players", "Gold=" + std::to_string(cost), filter);
    
    for (Item& item : items) {
        if (item.bought > 0) {
            std::map<std::string, std::string> filter2;
            std::map<std::string, std::string> filter3;
            int newQty = item.bought;

            filter2["Item"] = "(SELECT ID from items WHERE `Name`=\"" + item.Name + "\")";
            res = inst->runQuery(DBM::QueryType::SELECT, "inventory", "*", filter2);

            while (res->next())
            {
                filter3["ID"] = res->getString("ID");
                newQty = res->getInt("Quantity") + item.bought;
                inst->runQuery(DBM::QueryType::UPDATE, "inventory", "Quantity=" + std::to_string(newQty), filter3);
            }

            if (res->rowsCount() == 0) {
                std::map<std::string, std::string> filter4;
                filter4["Name"] = "\"" + item.Name + "\"";
                sql::ResultSet* res2 = inst->runQuery(DBM::QueryType::SELECT, "items", "ID", filter4);
                res2->next();
                inst->runQuery(DBM::QueryType::INSERT, "inventory (Player, Item, Quantity)", "(1, " + res2->getString("ID") + ", " + std::to_string(newQty) + ")", std::map<std::string, std::string>());
                delete res2;
            }
            
            delete res;

            item.quantity -= item.bought;
            item.bought = 0;
        }
    }
}

void charsButton_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        Menu* menu = nullptr;

        if (app->getMenu("itemSelect1234"))
        {
            menu = app->getMenu("itemSelect1234");
            menu->clear();
        }
        else
        {
            menu = app->addMenu("itemSelect1234");
        }
        
        generateShopContents();

        app->setActiveMenu("itemSelect1234");
        traveresedMenus.push_back("character1234");

        if (menu == nullptr)
            // Raise error if creating a menu fails
            throw MenuException("Could not create menu.");

        AddElement(menu, new Label(Point(350, 50), "Shop", "./res/Arial.ttf", 35), "title");

        std::cout << (menu == nullptr) << "\n";

        AddElement(menu, new Button(Point(100, 500), Point(350, 550), "Back", "./res/Arial.ttf", 25), "backBtn");
        AddElement(menu, new Button(Point(400, 500), Point(650, 550), "Buy", "./res/Arial.ttf", 25), "buyBtn");

        menu->getComponent("backBtn")->setOnClickAction(backButton_action);
        menu->getComponent("buyBtn")->setOnClickAction(db_update);
        unsigned factor = 0;
        for (const Item& item : items)
        {
            AddElement(menu, new Label(Point(50, 150 + 50 * factor), item.Name, "./res/Arial.ttf", 25), "item" + std::to_string(factor) + "title");

            AddElement(menu, new Button(Point(50, 185 + 50 * factor), Point(700, 186 + 50 * factor), "", "./res/Arial.ttf", 0), "Line" + std::to_string(factor));
            Converter::getButton(menu->getComponent("Line" + std::to_string(factor)))->getInternalButton().setFillColor(sf::Color::White);
            Converter::getButton(menu->getComponent("Line" + std::to_string(factor)))->getInternalButton().setOutlineThickness(1);

            AddElement(menu, new Label(Point(180, 160 + 50 * factor), "Stock: " + std::to_string(item.quantity), "./res/Arial.ttf", 15), "item" + std::to_string(factor) + "stock");
            AddElement(menu, new Label(Point(280, 160 + 50 * factor), "Price: " + std::to_string(item.price), "./res/Arial.ttf", 15), "item" + std::to_string(factor) + "price");

            AddElement(menu, new Label(Point(470, 160 + 50 * factor), "0", "./res/Arial.ttf", 15), "item" + std::to_string(factor) + "bought");

            AddElement(menu, new ItemFactory(Point(600, 150 + 50 * factor), Point(630, 180 + 50 * factor), "./res/plus.png", std::to_string(factor)), "itemPlus" + std::to_string(factor));
            AddElement(menu, new ItemFactory(Point(643, 153 + 50 * factor), Point(667, 177 + 50 * factor), "./res/minus.png", std::to_string(factor)), "itemMinus" + std::to_string(factor));
        
            menu->getComponent("itemPlus" + std::to_string(factor))->setOnClickAction(buy_item_action);
            menu->getComponent("itemMinus" + std::to_string(factor))->setOnClickAction(remove_item_action);

            factor++;
        }

        AddElement(menu, new Label(Point(440, 300), "Money: 0", "./res/Arial.ttf", 25), "priceDisplay");
        {
            std::wstring wstr(L"Money: ");
            std::wstring buffer;

            StringToWString(buffer, std::to_string(cost));
            wstr.append(buffer);

            easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("priceDisplay"))->getInternalText().setString(sf::String(wstr));
        }
    }
}

void worldsButton_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        app->setActiveMenu("worldSelect");
        traveresedMenus.push_back("second");
    }
}