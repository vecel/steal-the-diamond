#pragma once
#include "Object.h"

class TileMap
{
	friend class Level;

public:
	static const int HEIGHT = 25;
	static const int WIDTH = 40;

	TileMap(sf::RenderWindow* window);
	~TileMap();

	void setObjectAt(sf::Vector2i pos, Object* obj);
	void removeObjectAt(sf::Vector2i pos);
	void draw();
	void clear(); // <-TODO

	Object* operator[](sf::Vector2i pos);
	Object* getObjectAt(sf::Vector2i pos);

private:
	Object* tileSet[HEIGHT * WIDTH];
	sf::RenderWindow* window;
};

