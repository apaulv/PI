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