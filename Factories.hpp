
#pragma once

#include <iostream>
#include <Image.hpp>

extern std::string world;
extern std::string item;
extern int monsterID;

class WorldFactory : public easyGUI::Component
{
private:
	std::string worldId;
	easyGUI::Image img;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(img, states);
	}

public:
	WorldFactory(const easyGUI::Point& loc, const easyGUI::Point& fin, const std::string& path, const std::string& id) :
		img(loc, fin, path), worldId(id) {}
	
	virtual void onClick()
	{
		img.setContainer(_container);

		if (!isMouseHover())
			return;
		world = worldId;
		_onClick();
	}
	virtual bool isMouseHover() const
	{
		return img.isMouseHover();
	}

	virtual void updateLocation(const easyGUI::Point& newLoc)
	{
		img.updateLocation(newLoc);
	}
};

class ItemFactory : public easyGUI::Component
{
private:
	std::string worldId;
	easyGUI::Image img;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(img, states);
	}

public:
	ItemFactory(const easyGUI::Point& loc, const easyGUI::Point& fin, const std::string& path, const std::string& id) :
		img(loc, fin, path), worldId(id) {
	}

	virtual void onClick()
	{
		img.setContainer(_container);

		if (!isMouseHover())
			return;
		item = worldId;
		
		if(_onClick)
			_onClick();
	}
	virtual bool isMouseHover() const
	{
		return img.isMouseHover();
	}

	virtual void updateLocation(const easyGUI::Point& newLoc)
	{
		img.updateLocation(newLoc);
	}
};

class MonsterFactory : public easyGUI::Component
{
private:
	int worldId;
	easyGUI::Label img;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(img, states);
	}

public:
	MonsterFactory(const easyGUI::Point& loc, const std::string& text, const std::string& path, unsigned size, int id) :
		img(loc, text, path, size), worldId(id) {
		img.getInternalText().setFillColor(sf::Color::Red);
	}

	virtual void onClick()
	{
		img.setContainer(_container);

		if (!isMouseHover())
			return;
		monsterID = worldId;

		if (_onClick)
			_onClick();
	}
	virtual bool isMouseHover() const
	{
		return img.isMouseHover();
	}

	virtual void updateLocation(const easyGUI::Point& newLoc)
	{
		img.updateLocation(newLoc);
	}
};