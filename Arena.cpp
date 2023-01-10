#include "Arena.hpp"
#include "DBM.h"
#include <random>
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

std::vector<std::string> passives = std::vector<std::string>();
std::vector<std::string> actives = std::vector<std::string>();
std::vector<MonsterGroup> enemies = std::vector<MonsterGroup>();

void init()
{
	std::shared_ptr<DBM> inst = DBM::getInstance("127.0.0.1", "3306", "vap_pi", "root", "En3RgYm4x0u7");

	std::map<std::string, std::string> filter;
	filter["Passive"] = "1";

	sql::ResultSet* res = inst->runQuery(DBM::QueryType::SELECT, "actions", "Descr", filter);
	while (res->next()) {
		passives.push_back(res->getString("Descr"));
	}
	delete res;

	filter["Passive"] = "0";
	res = inst->runQuery(DBM::QueryType::SELECT, "actions", "Descr", filter);
	while (res->next()) {
		actives.push_back(res->getString("Descr"));
	}
	delete res;
}

Card MonsterGroup::drawCard() {
	Card card = abilities.back();

	std::cout << card.activeIndex << " ;; " << card.passiveIndex << "\n";

	abilities.pop_back();
	discarded.push_back(card);

	if (card.refresh)
	{
		for (const Card& item : discarded) {
			abilities.push_back(item);
		}

		discarded.clear();
		shuffle();
	}

	return card;
}

int myrandom(int i) { return std::rand() % i; }

void MonsterGroup::shuffle() {
	std::srand(unsigned(std::time(0)));
	std::random_shuffle(abilities.begin(), abilities.end());
}

Card MonsterGroup::generateCard(std::vector<int> forbiddenPassives, std::vector<int> forbiddenActives)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, passives.size()-1);
	std::uniform_int_distribution<> distr2(0, actives.size()-1);

	Card c;

	int index = distr(gen);
	while (std::find(forbiddenPassives.begin(), forbiddenPassives.end(), index) != forbiddenPassives.end())
		index = distr(gen);
	c.passiveIndex = index;

	index = distr2(gen);
	while (std::find(forbiddenActives.begin(), forbiddenActives.end(), index) != forbiddenActives.end())
		index = distr2(gen);
	c.activeIndex = index;

	return c;
}

void MonsterGroup::generateDeck() {
	std::vector<int> f1, f2;
	
	for (int i = 0; i < 7; i++) {
		abilities.push_back(generateCard(f1, f2));

		f1.push_back(abilities.back().passiveIndex);
		f1.push_back(abilities.back().activeIndex);

		if (i == 2 || i == 6)
			abilities.back().refresh = 1;
		else
			abilities.back().refresh = 0;
	}
}