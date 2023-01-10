#include "../buttons.hpp"

int players = 1;

void demoButton_action ()
{
    easyGUI::Application* app = nullptr;
    
    app = app->getInstance();

    if(app != nullptr)
    {
        easyGUI::Menu* menu = app->getActiveMenu();

        std::string user = easyGUI::Converter::getTextbox(menu->getComponent("uName"))->getText();
        std::string pass = easyGUI::Converter::getTextbox(menu->getComponent("pass"))->getText();

        if(user == "admin" && pass == "admin")
        {
            app->setActiveMenu("second");
            traveresedMenus.push_back("mainMenu");
        }
    }
}

void get_character()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        create_character_menu(app);
        app->setActiveMenu("character1234");
        traveresedMenus.push_back("second");
    }
}

int StringToWString(std::wstring& ws, const std::string& s)
{
    std::wstring wsTmp(s.begin(), s.end());

    ws = wsTmp;

    return 0;
}

void buy_item_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        int index = std::stoi(item);
        if (items[index].quantity > 0)
        {
            if (items[index].price > cost)
                return;

            items[index].bought++;
            items[index].quantity--;

            cost -= items[index].price;

            {
                std::wstring wstr(L"Stock: ");
                std::wstring buffer;

                StringToWString(buffer, std::to_string(items[index].quantity));
                wstr.append(buffer);

                easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("item" + item + "stock"))->getInternalText().setString(sf::String(wstr));
            }
            {
                std::wstring wstr(L" ");
                std::wstring buffer;

                StringToWString(buffer, std::to_string(items[index].bought));
                wstr.append(buffer);

                easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("item" + item + "bought"))->getInternalText().setString(sf::String(wstr));
            }
            {
                std::wstring wstr(L"Money: ");
                std::wstring buffer;

                StringToWString(buffer, std::to_string(cost));
                wstr.append(buffer);

                easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("priceDisplay"))->getInternalText().setString(sf::String(wstr));
            }
        }
    }
}

void add_players_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        if (players < 4)
        {
            players++;

            {
                std::wstring wstr(L"Players: ");
                std::wstring buffer;

                StringToWString(buffer, std::to_string(players));
                wstr.append(buffer);

                easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("Players"))->getInternalText().setString(sf::String(wstr));
            }
        }
    }
}

void remove_players_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        if (players > 1)
        {
            players--;

            {
                std::wstring wstr(L"Players: ");
                std::wstring buffer;

                StringToWString(buffer, std::to_string(players));
                wstr.append(buffer);

                easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("Players"))->getInternalText().setString(sf::String(wstr));
            }
        }
    }
}

void remove_item_action()
{
    easyGUI::Application* app = nullptr;

    app = app->getInstance();

    if (app != nullptr)
    {
        int index = std::stoi(item);
        if (items[index].bought > 0)
        {
            items[index].bought--;
            items[index].quantity++;

            cost += items[index].price;

            {
                std::wstring wstr(L"Stock: ");
                std::wstring buffer;

                StringToWString(buffer, std::to_string(items[index].quantity));
                wstr.append(buffer);

                easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("item" + item + "stock"))->getInternalText().setString(sf::String(wstr));
            }
            {
                std::wstring wstr(L" ");
                std::wstring buffer;

                StringToWString(buffer, std::to_string(items[index].bought));
                wstr.append(buffer);

                easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("item" + item + "bought"))->getInternalText().setString(sf::String(wstr));
            }
            {
                std::wstring wstr(L"Money: ");
                std::wstring buffer;

                StringToWString(buffer, std::to_string(cost));
                wstr.append(buffer);

                easyGUI::Converter::getLabel(app->getActiveMenu()->getComponent("priceDisplay"))->getInternalText().setString(sf::String(wstr));
            }
        }
    }
}