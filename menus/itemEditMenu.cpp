#include "../menus.hpp"
#include "buttons.hpp"

using namespace easyGUI;

void createItemEditMenu(Application* appInstance)
{
    if(appInstance == nullptr)
        // Raise error if application has not been created
        throw MenuException("Could not get hold of application instance.");

    Menu* menu = appInstance->addMenu("item1EditMenu");

    if(menu == nullptr)
        // Raise error if creating a menu fails
        throw MenuException("Could not create menu.");

    AddElement(menu, new Label(Point(350, 50), "Item 1", "./res/Arial.ttf", 35), "title");
    AddElement(menu, new Image(Point(460, 55), Point(490, 85), "./res/edit.png"), "editName");

    AddElement(menu, new Button(Point(50, 100), Point(700, 101), "", "./res/Arial.ttf", 0), "Line1");
    Converter::getButton(menu->getComponent("Line1"))->getInternalButton().setFillColor(sf::Color::White);
    Converter::getButton(menu->getComponent("Line1"))->getInternalButton().setOutlineThickness(1);

    AddElement(menu, new Image(Point(50, 150), Point(250, 300), "./res/image.jpeg"), "itempic");
    AddElement(menu, new Button(Point(320, 150), Point(321, 400), "", "./res/Arial.ttf", 0), "Line2");
    Converter::getButton(menu->getComponent("Line2"))->getInternalButton().setFillColor(sf::Color::White);
    Converter::getButton(menu->getComponent("Line2"))->getInternalButton().setOutlineThickness(1);

    AddElement(menu, new Label(Point(350, 150), "Rarirty: ", "./res/Arial.ttf", 40), "itemTitle");
    AddElement(menu, new Label(Point(500, 160), "LEGENDARY", "./res/Arial.ttf", 25), "rarity");
    Converter::getLabel(menu->getComponent("rarity"))->getInternalText().setFillColor(sf::Color::Yellow);
    AddElement(menu, new Image(Point(660, 160), Point(690, 190), "./res/edit.png"), "editRarity");

    AddElement(menu, new Label(Point(350, 200), "Price range: ", "./res/Arial.ttf", 40), "pRangeLabel");
    AddElement(menu, new Label(Point(580, 215), "100 - 200", "./res/Arial.ttf", 25), "range");
    AddElement(menu, new Image(Point(700, 215), Point(730, 245), "./res/edit.png"), "editPrice");

    AddElement(menu, new Label(Point(350, 300), "Allow for custom settings.", "./res/Arial.ttf", 25), "desc");    
    AddElement(menu, new Image(Point(660, 300), Point(690, 330), "./res/edit.png"), "editDescr");

    AddElement(menu, new Button(Point(100, 500), Point(350, 550), "Cancel", "./res/Arial.ttf", 25), "cancelBtn");
    AddElement(menu, new Button(Point(400, 500), Point(650, 550), "Save", "./res/Arial.ttf", 25), "saveBtn");

    menu->getComponent("cancelBtn")->setOnClickAction(backButton_action);
}
