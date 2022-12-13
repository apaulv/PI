#include "../menus.hpp"
#include "buttons.hpp"

using namespace easyGUI;

void createWorldMgmt(Application* appInst)
{
    if(appInst == nullptr)
        // Throw exception if application has not been created
        throw MenuException("Could not get hold of application instance.");
    
    Menu* menu = appInst->addMenu("world1Menu");   // <--- Adding a regular menu

    if(menu == nullptr)
        // Throw exception if menu could not be created
        throw MenuException("Could not create menu.");

    AddElement(menu, new Label(Point(300, 50), "World 1", "./res/Arial.ttf", 40), "title");
    AddElement(menu, new Button(Point(250, 150), Point(500, 200), "Creatures", "./res/Arial.ttf", 25), "creaturesBtn");
    AddElement(menu, new Button(Point(250, 250), Point(500, 300), "Items", "./res/Arial.ttf", 25), "itemsBtn");
    AddElement(menu, new Button(Point(250, 350), Point(500, 400), "Players", "./res/Arial.ttf", 25), "playersBtn");
    AddElement(menu, new Button(Point(250, 450), Point(500, 500), "Back", "./res/Arial.ttf", 25), "backBtn");

    menu->getComponent("backBtn")->setOnClickAction(backButton_action);
    menu->getComponent("itemsBtn")->setOnClickAction(get_items_action);
}
