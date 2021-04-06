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

	void addObjectToRemove(Object* obj);
	void removeOldObj();

	TileMap* tileMap;
	std::vector<Object*> objects;
	std::vector<Object*> objToRemove;
	Player* activePlayer;

private:
	//sf::RenderWindow* window;
};

