
#include "../menus.hpp"
#include "buttons.hpp"
#include <random>
#include <ctime>

using namespace easyGUI;

std::vector<Rarity> rarities;
std::vector<Item> items;

void generateShopContents()
{
    items.clear();
    rarities.clear();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Get worlds from DB
    std::shared_ptr<DBM> inst = DBM::getInstance("127.0.0.1", "3306", "vap_pi", "root", "En3RgYm4x0u7");

    if (!inst)
        throw MenuException("Could not connect to database.");

    sql::ResultSet* res = inst->runQuery(DBM::QueryType::SELECT, "rarities", "*", std::map<std::string, std::string>());

    while (res->next())
    {
        Rarity r;

        r.spawnChance = res->getDouble("SpawnChance");
        r.Name = res->getString("Name");
        r.highAmount = res->getInt64("HighStock");
        r.lowAmount = res->getInt64("LowStock");
        r.highPrice = res->getInt64("HighPrice");
        r.lowPrice = res->getInt64("LowPrice");
        r.id = res->getString("ID");

        rarities.push_back(r);
    }

    delete res;

    std::sort(rarities.begin(), rarities.end(), [](Rarity r1, Rarity r2) -> bool { return r1.spawnChance < r2.spawnChance;  });

    // Selecting 3 random rarities
    for (unsigned index = 0; index < 3; index++)
    {
        float rng = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        for (const Rarity& r : rarities) {
            if (rng <= r.spawnChance) {
                Item i;

                std::random_device rd; // obtain a random number from hardware
                std::mt19937 gen(rd()); // seed the generator
                std::uniform_int_distribution<> distr(r.lowAmount, r.highAmount);
                std::uniform_int_distribution<> distr2(r.lowPrice, r.highPrice);

                i.Name = "";
                i.rarity = r.id;
                i.price = distr2(gen);
                i.quantity = distr(gen);

                items.push_back(i);
                break;
            }
            else {
                rng -= r.spawnChance;
            }
        }
    }

    // Populating items
    for (Item& item : items)
    {
        std::map<std::string, std::string> filter;
        std::vector<std::string> candidates;
        filter["World"] = "1";
        filter["Rarity"] = item.rarity;

        res = inst->runQuery(DBM::QueryType::SELECT, "items", "*", filter);

        while (res->next())
        {
            candidates.push_back(res->getString("Name"));
        }

        delete res;

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, candidates.size() - 1);

        item.Name = candidates.at(distr(gen));
        std::cout << item.Name << " ";
    }
}

void createShopMenu(Application* appInstance)
{
    if (appInstance == nullptr)
        // Raise error if application has not been created
        throw MenuException("Could not get hold of application instance.");

    Menu* menu = appInstance->addMenu("itemSelect1234");

    if (menu == nullptr)
        // Raise error if creating a menu fails
        throw MenuException("Could not create menu.");

    AddElement(menu, new Label(Point(400, 50), "Shop", "./res/Arial.ttf", 35), "title");
}
