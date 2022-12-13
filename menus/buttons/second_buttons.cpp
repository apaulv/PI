#include "../buttons.hpp"

using namespace easyGUI;

void charsButton_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        app->setActiveMenu("itemSelect1234");
        traveresedMenus.push_back("second");
    
        generateShopContents();

        Menu* menu = app->getActiveMenu();

        unsigned factor = 0;
        for (const Item& item : items)
        {
            AddElement(menu, new Label(Point(50, 150 + 50 * factor), item.Name, "./res/Arial.ttf", 25), "item" + std::to_string(factor) + "title");

            AddElement(menu, new Button(Point(50, 185 + 50 * factor), Point(700, 186 + 50 * factor), "", "./res/Arial.ttf", 0), "Line" + std::to_string(factor));
            Converter::getButton(menu->getComponent("Line" + std::to_string(factor)))->getInternalButton().setFillColor(sf::Color::White);
            Converter::getButton(menu->getComponent("Line" + std::to_string(factor)))->getInternalButton().setOutlineThickness(1);

            AddElement(menu, new Label(Point(150, 160 + 50 * factor), "Stock: " + std::to_string(item.quantity), "./res/Arial.ttf", 15), "item" + std::to_string(factor) + "stock");
            AddElement(menu, new Label(Point(250, 160 + 50 * factor), "Price: " + std::to_string(item.price), "./res/Arial.ttf", 15), "item" + std::to_string(factor) + "price");

            AddElement(menu, new Image(Point(400, 150 + 50 * factor), Point(430, 180 + 50 * factor), "./res/plus.png"), "itemPlus" + std::to_string(factor));
            AddElement(menu, new Image(Point(440, 155 + 50 * factor), Point(470, 185 + 50 * factor), "./res/minus.png"), "itemMinus" + std::to_string(factor));
            factor++;
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