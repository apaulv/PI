
#pragma once

#include <iostream>
#include <Image.hpp>

extern std::string world;
extern std::string item;

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
		img(loc, fin, path), worldId(id) {}

	virtual void onClick()
	{
		item = worldId;
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