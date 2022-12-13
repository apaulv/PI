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


/**
 * @file buttons.hpp
 * @author David Bogdan (david.bnicolae@gmail.com)
 * @brief Includes the headers for all button callbacks
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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