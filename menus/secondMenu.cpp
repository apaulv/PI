#include "../menus.hpp"
#include "buttons.hpp"

using namespace easyGUI;

void createSecondMenu(Application* appInst)
{
    if(appInst == nullptr)
        // Throw exception if application has not been created
        throw MenuException("Could not get hold of application instance.");
    
    Menu* menu = appInst->addMenu("second");   // <--- Adding a regular menu

    if(menu == nullptr)
        // Throw exception if menu could not be created
        throw MenuException("Could not create menu.");

    AddElement(menu, new Label(Point(220, 100), "welcome, admin", "./res/Arial.ttf", 40), "title");
    AddElement(menu, new Button(Point(200, 400), Point(450, 450), "Go back", "./res/Arial.ttf", 25), "back");
    AddElement(menu, new Button(Point(200, 200), Point(450, 250), "Characters", "./res/Arial.ttf", 25), "chars");
    AddElement(menu, new Button(Point(200, 300), Point(450, 350), "Worlds", "./res/Arial.ttf", 25), "worlds");

    if(Converter::getButton(menu->getComponent("back")) != nullptr)
        menu->getComponent("back")->setOnClickAction(backButton_action);

    if (Converter::getButton(menu->getComponent("chars")) != nullptr)
        menu->getComponent("chars")->setOnClickAction(charsButton_action);

    if (Converter::getButton(menu->getComponent("worlds")) != nullptr)
        menu->getComponent("worlds")->setOnClickAction(worldsButton_action);
}
