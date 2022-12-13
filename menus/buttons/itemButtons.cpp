#include "../buttons.hpp"

void view_item_button ()
{
    easyGUI::Application* app = nullptr;
    
    app = app->getInstance();

    if(app != nullptr)
    {
        app->setActiveMenu("item" + item + "ViewMenu");
        traveresedMenus.push_back("itemSelect");

        for(easyGUI::Component* element : app->getActiveMenu()->getAllComponents()) {
            easyGUI::TextBox* box = easyGUI::Converter::getTextbox(element);

            if(!box)
                continue;
            box->clear();
        }
    }
}

void edit_item_action ()
{
    easyGUI::Application* app = nullptr;
    
    app = app->getInstance();

    if(app != nullptr)
    {
        app->setActiveMenu("item" + item + "EditMenu");
        traveresedMenus.push_back("itemSelect");

        for(easyGUI::Component* element : app->getActiveMenu()->getAllComponents()) {
            easyGUI::TextBox* box = easyGUI::Converter::getTextbox(element);

            if(!box)
                continue;
            box->clear();
        }
    }
}

void create_item_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        app->setActiveMenu("itemCreate");
        traveresedMenus.push_back("world" + world + "Menu");

        for (easyGUI::Component* element : app->getActiveMenu()->getAllComponents()) {
            easyGUI::TextBox* box = easyGUI::Converter::getTextbox(element);

            if (!box)
                continue;
            box->clear();
        }
    }
}

void get_items_action()
{
    easyGUI::Application* app = nullptr;
    
    app = app->getInstance();

    if(app != nullptr)
    {
        app->setActiveMenu("itemSelect");
        traveresedMenus.push_back("world" + world + "Menu");

        for(easyGUI::Component* element : app->getActiveMenu()->getAllComponents()) {
            easyGUI::TextBox* box = easyGUI::Converter::getTextbox(element);

            if(!box)
                continue;
            box->clear();
        }
    }  
}