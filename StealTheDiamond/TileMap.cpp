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
			std::string tileGraphics;
			levelData >> tileType >> tileGraphics;

			layer0[j + i * WIDTH] = tileType;

			sf::Vector2f txtPix;

			txtPix = tilesTextures[tileGraphics];

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


	// fuckup
	tilesTextures["grass"] = sf::Vector2f(0, 0);
	tilesTextures["grass1"] = sf::Vector2f(tileSize, 0);
	tilesTextures["grass2"] = sf::Vector2f(2 * tileSize, 0);
	tilesTextures["grass3"] = sf::Vector2f(3 * tileSize, 0);
	tilesTextures["grass4"] = sf::Vector2f(4 * tileSize, 0);
	tilesTextures["sand"] = sf::Vector2f(5 * tileSize, 0);
	tilesTextures["water"] = sf::Vector2f(6 * tileSize, 0);
	tilesTextures["box_under_water"] = sf::Vector2f(7 * tileSize, 0);
	tilesTextures["grass5"] = sf::Vector2f(0, tileSize);
	tilesTextures["grass6"] = sf::Vector2f(tileSize, tileSize);
	tilesTextures["grass7"] = sf::Vector2f(2 * tileSize, tileSize);
	tilesTextures["grass8"] = sf::Vector2f(3 * tileSize, tileSize);
	tilesTextures["void"] = sf::Vector2f(4 * tileSize, tileSize);
	tilesTextures["void1"] = sf::Vector2f(5 * tileSize, tileSize);
	tilesTextures["void2"] = sf::Vector2f(6 * tileSize, tileSize);
	tilesTextures["void3"] = sf::Vector2f(7 * tileSize, tileSize);
	tilesTextures["void4"] = sf::Vector2f(0, 2 * tileSize);
	tilesTextures["sand1"] = sf::Vector2f(tileSize, 2 * tileSize);
	tilesTextures["sand2"] = sf::Vector2f(2 * tileSize, 2 * tileSize);
	tilesTextures["sand3"] = sf::Vector2f(3 * tileSize, 2 * tileSize);
	tilesTextures["sand4"] = sf::Vector2f(4 * tileSize, 2 * tileSize);
	tilesTextures["void5"] = sf::Vector2f(5 * tileSize, 2 * tileSize);
	tilesTextures["void6"] = sf::Vector2f(6 * tileSize, 2 * tileSize);
	tilesTextures["void7"] = sf::Vector2f(7 * tileSize, 2 * tileSize);
	tilesTextures["void8"] = sf::Vector2f(0, 3 * tileSize);
}


