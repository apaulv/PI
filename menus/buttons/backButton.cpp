#include "../buttons.hpp"

std::vector<std::string> traveresedMenus = std::vector<std::string>();

void backButton_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        if (traveresedMenus.back() == "character1234")
            create_character_menu(app);

        app->setActiveMenu(traveresedMenus.back());
        traveresedMenus.pop_back();

        for (easyGUI::Component* element : app->getActiveMenu()->getAllComponents()) {
            easyGUI::TextBox* box = easyGUI::Converter::getTextbox(element);

            if (!box)
                continue;
            box->clear();
        }
    }
}