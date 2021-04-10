#include <fstream>
#include <iostream>
#include "TileMap.h"
#include "Object.h"
#include "Wall.h"
#include "Player.h"

TileMap::TileMap(sf::RenderWindow* window, std::string txtAsset) {
	printf("TileMap constructor\n");
	this->window = window;

	if (!tilesAsset.loadFromFile(txtAsset)) printf("Cannot load tilesAssets\n");
	//if (!exit.loadFromFile("textures\\door.png")) printf("Cannot load exit's texture\n");

	setUpTexturesMap();
}

TileMap::~TileMap() {
	printf("TileMap destructor\n");
}

bool TileMap::loadLayer0(std::fstream& levelData, int tileSize) {

	int exitX, exitY;

	levelData.ignore(1000, ':'); // ignore descriptions in level data file
	levelData >> exitX >> exitY;

	exit = new Exit(sf::Vector2i(exitX, exitY), "textures\\exit.png");

	backgroundTiles.setPrimitiveType(sf::Quads);
	backgroundTiles.resize(WIDTH * HEIGHT * 4);

	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {

			int tileType;
			levelData >> tileType;


			// if-else must be updated every time a tile/tile graphics is added
			Ground ground;
			if (tileType >= 0 && tileType <= 32) ground = LAND;
			else if (tileType > 32 && tileType <= 48) ground = VOID;
			else if (tileType == 49) ground = WATER;
			else if (tileType == 60) ground = BOX_IN_WATER;
			
			layer0[j + i * WIDTH] = ground;

			sf::Vector2f txtPix;

			txtPix = tilesTextures[tileType];

			sf::Vertex* quad = &backgroundTiles[(j + i * WIDTH) * 4];

			quad[0].position = sf::Vector2f(j * tileSize, i * tileSize);
			quad[1].position = sf::Vector2f((j + 1) * tileSize, i * tileSize);
			quad[2].position = sf::Vector2f((j + 1) * tileSize, (i + 1) * tileSize);
			quad[3].position = sf::Vector2f(j * tileSize, (i + 1) * tileSize);

			quad[0].texCoords = sf::Vector2f(txtPix.x, txtPix.y);
			quad[1].texCoords = sf::Vector2f(txtPix.x + tileSize, txtPix.y);
			quad[2].texCoords = sf::Vector2f(txtPix.x + tileSize, txtPix.y + tileSize);
			quad[3].texCoords = sf::Vector2f(txtPix.x, txtPix.y + tileSize);
		}
	}

	sf::Transform transform;
	transform.translate(sf::Vector2f(10.0f, 10.0f));

	states.transform = transform;
	states.texture = &tilesAsset;
	
	printf("layer 0\n");
	return true;
}

void TileMap::loadLayer1(std::vector<Object*> objects) {
	for (Object* obj : objects) layer1[obj->position.x + obj->position.y * WIDTH] = obj;
}

void TileMap::setObjectAt(sf::Vector2i pos, Object* obj) {
	layer1[pos.x + pos.y * WIDTH] = obj;
}

void TileMap::fillWater(sf::Vector2i pos) {

	if (layer0[pos.x + pos.y * WIDTH] == WATER) {
		std::cout << "water " << pos.x << " " << pos.y << '\n';

		layer0[pos.x + pos.y * WIDTH] = BOX_IN_WATER;

		sf::Vertex* quad = &backgroundTiles[(pos.x + pos.y * WIDTH) * 4];

		// change texture to box in the water
		sf::Vector2f txtPix(7 * tileSize, 0);
		quad[0].texCoords = sf::Vector2f(txtPix.x, txtPix.y);
		quad[1].texCoords = sf::Vector2f(txtPix.x + tileSize, txtPix.y);
		quad[2].texCoords = sf::Vector2f(txtPix.x + tileSize, txtPix.y + tileSize);
		quad[3].texCoords = sf::Vector2f(txtPix.x, txtPix.y + tileSize);
	}
}

void TileMap::showExit() {
	isExitShown = true;
	layer0[exit->position.x + exit->position.y * WIDTH] = EXIT;
}

void TileMap::removeObjectAt(sf::Vector2i pos) {
	layer1[pos.x + pos.y * WIDTH] = nullptr;
}

void TileMap::draw() {

	window->draw(backgroundTiles, states);

	if(isExitShown) window->draw(*exit);

	for (Object* obj : layer1) if(obj != nullptr) obj->draw(*window, sf::RenderStates::Default);

}

void TileMap::clear() {
	
	printf("tileMap cleared\n");
}

Object* TileMap::getObjectAt(sf::Vector2i pos) {
	return layer1[pos.x + pos.y * WIDTH];
}

int TileMap::getGroundTypeAt(sf::Vector2i pos) {
	return layer0[pos.x + pos.y * WIDTH];
}




void TileMap::setUpTexturesMap() {
	int txtCount = 64;
	tilesTextures.reserve(txtCount);

	// 0 - 32 LAND
	tilesTextures[0] = sf::Vector2f(0, 0); // grass
	tilesTextures[1] = sf::Vector2f(tileSize, 0);
	tilesTextures[2] = sf::Vector2f(2 * tileSize, 0);
	tilesTextures[3] = sf::Vector2f(3 * tileSize, 0);
	tilesTextures[4] = sf::Vector2f(4 * tileSize, 0);
	tilesTextures[5] = sf::Vector2f(5 * tileSize, 0); // sand
	tilesTextures[6] = sf::Vector2f(0, tileSize);
	tilesTextures[7] = sf::Vector2f(tileSize, tileSize);
	tilesTextures[8] = sf::Vector2f(2 * tileSize, tileSize);
	tilesTextures[9] = sf::Vector2f(3 * tileSize, tileSize);
	tilesTextures[10] = sf::Vector2f(tileSize, 2 * tileSize); 
	tilesTextures[11] = sf::Vector2f(2 * tileSize, 2 * tileSize);
	tilesTextures[12] = sf::Vector2f(3 * tileSize, 2 * tileSize);
	tilesTextures[13] = sf::Vector2f(4 * tileSize, 2 * tileSize);
	
	// 33 - 48 VOID
	tilesTextures[33] = sf::Vector2f(4 * tileSize, tileSize);
	tilesTextures[34] = sf::Vector2f(5 * tileSize, tileSize);
	tilesTextures[35] = sf::Vector2f(6 * tileSize, tileSize);
	tilesTextures[36] = sf::Vector2f(7 * tileSize, tileSize);
	tilesTextures[37] = sf::Vector2f(0, 2 * tileSize);
	tilesTextures[38] = sf::Vector2f(5 * tileSize, 2 * tileSize);
	tilesTextures[39] = sf::Vector2f(6 * tileSize, 2 * tileSize);
	tilesTextures[40] = sf::Vector2f(7 * tileSize, 2 * tileSize);
	tilesTextures[41] = sf::Vector2f(0, 3 * tileSize);

	tilesTextures[49] = sf::Vector2f(6 * tileSize, 0); // water 49
	tilesTextures[60] = sf::Vector2f(7 * tileSize, 0); // box_in_water 60
}


