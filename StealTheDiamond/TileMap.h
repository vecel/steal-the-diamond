#pragma once
#include "Object.h"
#include <unordered_map>
#include "Exit.h"

class TileMap
{
	friend class Level;

public:
	static const int HEIGHT = 25;
	static const int WIDTH = 40;
	static const int tileSize = 32;

	enum Ground {
		LAND = 0,
		VOID = 1,
		WATER = 2,
		BOX_IN_WATER = 3,
		ICE = 4,
		EXIT = 5
	};

	std::unordered_map<int, sf::Vector2f> tilesTextures;

	TileMap(sf::RenderWindow* window, std::string txtAsset);
	~TileMap();

	bool loadBackground(std::fstream& levelData, int tileSize = 32);
	void loadObjects(std::vector<Object*> objects);

	void setObjectAt(sf::Vector2i pos, Object* obj, int layer = 1);

	void fillWater(sf::Vector2i pos);
	void showExit();

	void removeObjectAt(sf::Vector2i pos, int layer = 1);
	void draw();
	void clear(); // <-TODO

	Object* getObjectAt(sf::Vector2i pos, int layer = 1);
	int getGroundTypeAt(sf::Vector2i pos);

	Exit* exit;
	bool isExitShown = false;

private:
	sf::RenderWindow* window;
	void setUpTexturesMap();

	/*
		objects layer first HEIGHT*WIDTH objects are layer 0, second HEIGHT*WIDTH objects are layer 1
		layer0 stores objects that player (or other objects) can stand on
		layer1 stores other objects
	*/
	Object* objectsLayer[HEIGHT * WIDTH * 2];

	// background layer
	int backgroundLayer[HEIGHT * WIDTH];

	sf::Texture tilesAsset;
	sf::VertexArray backgroundTiles;

	sf::RenderStates states;
};

