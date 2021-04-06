#pragma once
#include "Object.h"

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
		ICE = 4
	};

	TileMap(sf::RenderWindow* window);
	~TileMap();

	bool loadLayer0(std::fstream& levelData, std::string txtAsset, int tileSize = 32);
	void loadLayer1(std::vector<Object*> objects);

	void setObjectAt(sf::Vector2i pos, Object* obj);

	void fillWater(sf::Vector2i pos);

	void removeObjectAt(sf::Vector2i pos);
	void draw();
	void clear(); // <-TODO

	Object* getObjectAt(sf::Vector2i pos);
	int getGroundTypeAt(sf::Vector2i pos);

private:
	sf::RenderWindow* window;

	// objects layer
	Object* layer1[HEIGHT * WIDTH];

	// background layer
	int layer0[HEIGHT * WIDTH];

	sf::Texture tilesAsset;
	sf::VertexArray backgroundTiles;

	sf::RenderStates states;
};

