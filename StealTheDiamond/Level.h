#pragma once
#include "Object.h"
#include "TileMap.h"
#include "Player.h"
#include <vector>

class Level
{
public:
	Level(sf::RenderWindow* w, std::string filePath);
	~Level();

	void loadFromFile(std::string path);
	void draw();

	TileMap tileMap;
	std::vector<Object*> objects;
	Player* activePlayer;

private:
	//sf::RenderWindow* window;
};

