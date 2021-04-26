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

	/*
		onRender function called after level is created, set objects animations here
	*/
	void onRender();
	void updateLevel();

	void addObjectToRemove(Object* obj);
	void removeOldObj();

	bool switchActivePlayer();
	void onPlayerDeath();

	sf::Vector2i getTextureStartingPoint(int id);

	sf::Clock clock;
	TileMap* tileMap;
	std::vector<Object*> objects;
	std::vector<Object*> objToRemove;
	std::vector<Player*> players;
	int playerIndex;
	Player* activePlayer;
	int diamonds;
	int diamondsToCollect;
	std::vector<sf::Vector2i> objectTextures;

private:
	void setUpObjectTextures();
	void loadObjects(std::fstream &levelData);
};

