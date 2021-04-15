#pragma once
#include "TileMap.h"
#include <vector>
#include "Object.h"
#include "Player.h"

class Level
{
public:
	static const float tileSize;

	Level(sf::RenderWindow* window, std::string filePath);
	~Level();

	void loadFromFile(std::string path);
	void draw();

	void updateLevel();

	void addObjectToRemove(Object* obj);
	void removeOldObj();

	sf::Vector2i getTextureStartingPoint(int id);

	sf::Clock clock;
	TileMap* tileMap;
	std::vector<Object*> objects;
	std::vector<Object*> objToRemove;
	Player* activePlayer;
	int diamonds;
	int diamondsToCollect;
	std::vector<sf::Vector2i> objectTextures;

private:
	void setUpObjectTextures();
	void loadObjects(std::fstream &levelData);
};

