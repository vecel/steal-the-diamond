#pragma once
#include "TileMap.h"
#include <vector>
#include "Object.h"
#include "Player.h"

class Level
{
public:
	Level(sf::RenderWindow* window, std::string filePath);
	~Level();

	void loadFromFile(std::string path);
	void draw();

	TileMap* tileMap;
	std::vector<Object*> objects;
	Player* activePlayer;

private:
	//sf::RenderWindow* window;
};

