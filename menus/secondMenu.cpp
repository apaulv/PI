// Copyright © 2022 David Bogdan

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
// (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, 
// publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do 
// so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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