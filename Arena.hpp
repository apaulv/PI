#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <Component.hpp>
#include <vector>
#include <string>

extern std::vector<std::string> passives;
extern std::vector<std::string> actives;

struct Card {
	int passiveIndex;
	int activeIndex;
	int refresh;
};

using Deck = std::vector<Card>;

struct MonsterGroup {
	std::string imagePath;
	std::string name;
	Deck abilities;
	Deck discarded;

	int monsters = 0;
	int strongMonsters = 0;
	int initiative = 0;

	void generateDeck();
	void shuffle();

	Card drawCard();
	Card generateCard(std::vector<int> forbiddenPassives, std::vector<int> forbiddenActives);
};

extern std::vector<MonsterGroup> enemies;

void init();

class Border : public easyGUI::Component {
private:
	sf::RectangleShape _shape;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(_shape, states);
	}

public:
	Border(easyGUI::Point p1, easyGUI::Point p2) {
		_shape.setPosition(p1.Xcoord, p1.Ycoord);
		_shape.setSize(sf::Vector2f(p2.Xcoord - p1.Xcoord, p2.Ycoord - p1.Ycoord));
		_shape.setOutlineColor(sf::Color::White);
		_shape.setFillColor(sf::Color::Black);
		_shape.setOutlineThickness(7);
	}

	bool isMouseHover() const {
		return false;
	}

	void updateLocation(const easyGUI::Point& p) {
		// pass
	}
};

class MyCheckBox : public easyGUI::Component {
private:
	sf::RectangleShape _shape;
	sf::RectangleShape _filler;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(_shape, states);

		if (checked)
			target.draw(_filler, states);
	}

public:
	bool checked;

	MyCheckBox(easyGUI::Point p1, easyGUI::Point p2) {
		_shape.setPosition(p1.Xcoord, p1.Ycoord);
		_shape.setSize(sf::Vector2f(p2.Xcoord - p1.Xcoord, p2.Ycoord - p1.Ycoord));
		_shape.setOutlineColor(sf::Color::White);
		_shape.setFillColor(sf::Color::Black);
		_shape.setOutlineThickness(2);

		_filler.setPosition(p1.Xcoord + 5, p1.Ycoord + 5);
		_filler.setSize(::sf::Vector2f(p2.Xcoord - p1.Xcoord - 10, p2.Ycoord - p1.Ycoord - 10));
		_filler.setFillColor(::sf::Color::White);
	}

	bool isMouseHover() const {
		if (_container != nullptr)
		{
			::sf::Vector2i currentPosition = ::sf::Mouse::getPosition(*_container);
			::sf::Vector2f worldPos = _container->mapPixelToCoords(currentPosition);

			if (_shape.getGlobalBounds().contains(worldPos.x, worldPos.y))
				return true;
		}

		return false;
	}

	void updateLocation(const easyGUI::Point& p) {
		// pass
	}

	void onClick()
	{
		if (isMouseHover())
		{
			checked = !checked;
		}
	}
};