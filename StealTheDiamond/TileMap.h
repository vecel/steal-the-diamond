#pragma once
#include "Object.h"

class TileMap
{
public:
	static const int HEIGHT = 20;
	static const int WIDTH = 40;

	TileMap(sf::RenderWindow* w);
	~TileMap();

	void loadFromFile(/*Level albo string albo ?? */);
	void draw();
	void clear();

private:
	sf::RenderWindow* window;
	Object* tileMap[WIDTH][HEIGHT];
};

