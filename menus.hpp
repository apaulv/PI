#pragma once

// Including dependencies
#include <Application.hpp>
#include <Exceptions/AssetException.hpp>
#include <Label.hpp>
#include <AlignmentTool.hpp>
#include <Button.hpp>
#include <PasswordBox.hpp>
#include <Textbox.hpp>
#include <Image.hpp>
#include <Menu.hpp>
#include <Point.hpp>
#include <Logger.hpp>
#include <Exceptions/MenuException.hpp>
#include "DBM.h"

// Defining functions to create menus
void createMainMenu(easyGUI::Application* appInstance);
void createSecondMenu(easyGUI::Application* appInstance);
void createWorldSelect(easyGUI::Application* appInstance);

void createWorldMgmt(easyGUI::Application* appInstance);
void createItemViewMenu(easyGUI::Application* appInstance);
void createItemEditMenu(easyGUI::Application* appInstance);
void createItemsMenu(easyGUI::Application* appInstance);
void createItemCreateMenu(easyGUI::Application* appInstance);

void createShopMenu(easyGUI::Application* appInstance);
