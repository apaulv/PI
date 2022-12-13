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

    unsigned quantity;
    unsigned price;
};

extern std::vector<std::string> traveresedMenus;
extern std::vector<Rarity> rarities;
extern std::vector<Item> items;

// First menu buttons

void demoButton_action();

// Second menu buttons

void backButton_action();
void charsButton_action();
void worldsButton_action();

// Third menu buttons

void view_world_action();
void view_item_button();
void edit_item_action();
void get_items_action();
void generateShopContents();
void create_item_action();
