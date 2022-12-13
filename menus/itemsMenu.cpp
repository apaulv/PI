#include "../menus.hpp"
#include "buttons.hpp"

using namespace easyGUI;

void createItemsMenu(Application* appInstance)
{
    if(appInstance == nullptr)
        // Raise error if application has not been created
        throw MenuException("Could not get hold of application instance.");

    Menu* menu = appInstance->addMenu("itemSelect");

    if(menu == nullptr)
        // Raise error if creating a menu fails
        throw MenuException("Could not create menu.");

    // Get worlds from DB
    std::shared_ptr<DBM> inst = DBM::getInstance("127.0.0.1", "3306", "vap_pi", "root", "En3RgYm4x0u7");

    if (!inst)
        throw MenuException("Could not connect to database.");
    std::map<std::string, std::string> filter;
    filter["World"] = "1";
   
    sql::ResultSet* res = inst->runQuery(DBM::QueryType::SELECT, "items", "*", filter);

    AddElement(menu, new Label(Point(300, 50), "Items", "./res/Arial.ttf", 35), "title");
    
    while (res->next())
    {
        AddElement(menu, new Label(Point(50, 150), res->getString("Name"), "./res/Arial.ttf", 25), "WorldName" + res->getString("ID"));

        AddElement(menu, new ItemFactory(Point(590, 150), Point(620, 180), "./res/view.png", res->getString("ID")), "viewBtn" + res->getString("ID"));
        AddElement(menu, new ItemFactory(Point(630, 150), Point(660, 180), "./res/edit.png", res->getString("ID")), "editBtn" + res->getString("ID"));
        AddElement(menu, new ItemFactory(Point(670, 150), Point(700, 180), "./res/delete.png", res->getString("ID")), "deleteBtn" + res->getString("ID"));

        AddElement(menu, new Button(Point(50, 185), Point(700, 186), "", "./res/Arial.ttf", 0), "Line" + res->getString("ID"));
        Converter::getButton(menu->getComponent("Line" + res->getString("ID")))->getInternalButton().setFillColor(sf::Color::White);
        Converter::getButton(menu->getComponent("Line" + res->getString("ID")))->getInternalButton().setOutlineThickness(1);

        menu->getComponent("viewBtn" + res->getString("ID"))->setOnClickAction(view_item_button);
        menu->getComponent("editBtn" + res->getString("ID"))->setOnClickAction(edit_item_action);
    }

    delete res;


    AddElement(menu, new Button(Point(150, 400), Point(400, 450), "Back", "./res/Arial.ttf", 25), "backBtn");
    AddElement(menu, new Button(Point(450, 400), Point(700, 450), "Add item", "./res/Arial.ttf", 25), "itemCreate");

    menu->getComponent("backBtn")->setOnClickAction(backButton_action);
    menu->getComponent("itemCreate")->setOnClickAction(create_item_action);
}
