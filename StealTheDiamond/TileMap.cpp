#include <fstream>
#include <iostream>
#include "TileMap.h"
#include "Object.h"
#include "Wall.h"
#include "Player.h"

TileMap::TileMap(sf::RenderWindow* window) {
	printf("TileMap constructor\n");
	this->window = window;
}

TileMap::~TileMap() {
	printf("TileMap destructor\n");
}

bool TileMap::loadLayer0(std::fstream& levelData, std::string txtAsset, int tileSize) {
	
	if (!tilesAsset.loadFromFile(txtAsset)) return false;

	backgroundTiles.setPrimitiveType(sf::Quads);
	backgroundTiles.resize(WIDTH * HEIGHT * 4);

	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {

			int tileType;
			levelData >> tileType;

			layer0[j + i * WIDTH] = tileType;

			sf::Vector2f txtPix;

			switch (tileType) {
			case 0: txtPix = sf::Vector2f(0, 0); break;
			case 1: txtPix = sf::Vector2f(4 * tileSize, tileSize); break;
			case 2: txtPix = sf::Vector2f(6 * tileSize, 0); break;
			}

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
	transform.translate(sf::Vector2f(10, 10));

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

void TileMap::removeObjectAt(sf::Vector2i pos) {
	layer1[pos.x + pos.y * WIDTH] = nullptr;
}

void TileMap::draw() {

	window->draw(backgroundTiles, states);
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


