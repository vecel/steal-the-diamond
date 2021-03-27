#pragma once
#include "Object.h"
#include <map>

class TileMap
{
	friend class Level;

	struct Comparator {
		bool operator()(sf::Vector2i v1, sf::Vector2i v2) const;
	};

public:
	static const int HEIGHT = 25;
	static const int WIDTH = 40;

	std::map<sf::Vector2i, Object*, Comparator> tileSet;

	TileMap();
	~TileMap();

	void insert(sf::Vector2i pos, Object* obj);
	void erase(sf::Vector2i pos);
	void draw();
	void clear();

private:
	sf::RenderWindow* window;

	void setWindow(sf::RenderWindow* w);
};

