#include "../menus.hpp"
#include "buttons.hpp"

using namespace easyGUI;

void createMainMenu(Application* appInstance)
{
    if(appInstance == nullptr)
        // Raise error if application has not been created
        throw MenuException("Could not get hold of application instance.");

    Menu* menu = appInstance->addMenu("mainMenu", true);   // Adds a new MAIN menu

    if(menu == nullptr)
        // Raise error if creating a menu fails
        throw MenuException("Could not create menu.");

    AddElement(menu,                // <--- The menu where the component is appended
        new Label(                  // <--- The type of component being appended
            Point(220, 100),        // <--- The position of the component
            "Game manager",         // <--- The text of the label
            "./res/Arial.ttf",      // <--- The font of the label
            40),                    // <--- Desired character size

        "title"                     // <--- A unique ID for the component
    );

    AddElement(menu, new Label(Point(100, 210), "Username", "./res/Arial.ttf", 25), "uNameLabel");
    AddElement(menu, new Label(Point(100, 310), "Password", "./res/Arial.ttf", 25), "passLabel");
    AddElement(menu, new Label(Point(270, 500), "Login with admin / admin", "./res/Arial.ttf", 15), "hint");

    AddElement(menu, 
        new TextBox(
            Point(250, 200),        // <--- Tpp-left corner of the box
            Point(500, 250),        // <--- Bottom-right corner of the box
            "./res/Arial.ttf",      // <--- Font of the text
            25),                    // <--- Desired character size
            
        "uName"
    );
    
    AddElement(menu, new PasswordBox(Point(250, 300), Point(500, 350), "./res/Arial.ttf", 25), "pass");
    
    AddElement(menu, 
        new Button(
            Point(250, 400),        // <--- The top-left of the button
            Point(500, 450),        // <--- The bottom-right corner of the button
            "Sign in",              // <--- The text of the button
            "./res/Arial.ttf",      // <--- The font of the text
            25),                    // <--- Desired character size
    
        "submit"
    );
     
    if(Converter::getButton(menu->getComponent("submit")) != nullptr)
        menu->getComponent("submit")->setOnClickAction(demoButton_action);     // <--- Adding a callback to be executed on mouse press
}