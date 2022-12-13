#include "../buttons.hpp"

void view_world_action ()
{
    easyGUI::Application* app = nullptr;
    
    app = app->getInstance();

    if(app != nullptr)
    {
        app->setActiveMenu("world" + world + "Menu");
        traveresedMenus.push_back("worldSelect");

        for(easyGUI::Component* element : app->getActiveMenu()->getAllComponents()) {
            easyGUI::TextBox* box = easyGUI::Converter::getTextbox(element);

            if(!box)
                continue;
            box->clear();
        }
    }
}