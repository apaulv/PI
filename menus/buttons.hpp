#pragma once

// Dependencies
#include <Application.hpp>
#include <Menu.hpp>
#include <Converter.hpp>
#include <vector>
#include <string>

#include "../Factories.hpp"

struct Rarity
{
    float spawnChance;

    unsigned lowAmount, highAmount;
    unsigned lowPrice, highPrice;
    std::string id;
    std::string Name;
};

struct Item
{
    std::string Name;
    std::string rarity;
    std::string ID;

    unsigned quantity;
    unsigned price;
    unsigned bought;
};

extern std::vector<std::string> traveresedMenus;
extern std::vector<Rarity> rarities;
extern std::vector<Item> items;
extern int cost;
extern int players;

// First menu buttons

void demoButton_action();

// Second menu buttons

void backButton_action();
void charsButton_action();
void get_character();
void worldsButton_action();

// Third menu buttons

void view_world_action();
void view_item_button();
void edit_item_action();
void get_items_action();
void generateShopContents();
void create_item_action();

int StringToWString(std::wstring& ws, const std::string& s);
void buy_item_action();
void remove_item_action();

void create_character_menu(easyGUI::Application* app);

void remove_players_action();
void add_players_action();