#include "../menus.hpp"
#include "buttons.hpp"

using namespace easyGUI;

std::string world = "";
std::string item = "";

void createWorldSelect(Application* appInstance)
{
    if(appInstance == nullptr)
        // Raise error if application has not been created
        throw MenuException("Could not get hold of application instance.");

    Menu* menu = appInstance->addMenu("worldSelect");   // Adds a new MAIN menu

    if(menu == nullptr)
        // Raise error if creating a menu fails
        throw MenuException("Could not create menu.");

    // Get worlds from DB
    std::shared_ptr<DBM> inst = DBM::getInstance("127.0.0.1", "3306", "vap_pi", "root", "En3RgYm4x0u7");

    if (!inst)
        throw MenuException("Could not connect to database.");
    sql::ResultSet* res = inst->runQuery(DBM::QueryType::SELECT, "worlds", "*", std::map<std::string, std::string>());

    unsigned offsetFactor = 0;
    while (res->next())
    {
        AddElement(menu, new Label(Point(50, 150 + 50 * offsetFactor), res->getString("Name"), "./res/Arial.ttf", 25), "WorldName1");

        AddElement(menu, new WorldFactory(Point(630, 150 + 50 * offsetFactor), Point(660, 180 + 50 * offsetFactor), "./res/view.png", res->getString("ID")), "viewBtn" + res->getInt("ID"));
        AddElement(menu, new Image(Point(670, 150 + 50 * offsetFactor), Point(700, 180 + 50 * offsetFactor), "./res/delete.png"), "deleteBtn" + res->getInt("ID"));

        AddElement(menu, new Button(Point(50, 185 + 50 * offsetFactor), Point(700, 186 + 50 * offsetFactor), "", "./res/Arial.ttf", 0), "Line" + res->getInt("ID"));
        Converter::getButton(menu->getComponent("Line" + res->getInt("ID")))->getInternalButton().setFillColor(sf::Color::White);
        Converter::getButton(menu->getComponent("Line" + res->getInt("ID")))->getInternalButton().setOutlineThickness(1);

        menu->getComponent("viewBtn" + res->getInt("ID"))->setOnClickAction(view_world_action);
    }

    delete res;

    AddElement(menu, new Label(Point(250, 50), "Select the world", "./res/Arial.ttf", 35), "title");
    AddElement(menu, new Button(Point(250, 400), Point(500, 450), "Back", "./res/Arial.ttf", 25), "backBtn");

    menu->getComponent("backBtn")->setOnClickAction(backButton_action);
}
