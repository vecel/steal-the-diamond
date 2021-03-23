#include "TileMap.h"
#include "Object.h"
#include "Wall.h"

TileMap::TileMap(sf::RenderWindow* w) {
	window = w;

	// paste code below to loadFromFile function and change it
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; ++j) {
			tileMap[i][j] = new Wall(i, j);
		}
	}
}

TileMap::~TileMap() {
	printf("TileMap destructor\n");
}

void TileMap::loadFromFile(/*arg*/) {

}

void TileMap::draw() {
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; ++j) {
			if(tileMap[i][j] != nullptr) tileMap[i][j]->draw(*window, sf::RenderStates::Default);
		}
	}
}

void TileMap::clear() {
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; ++j) {
			if (tileMap[i][j] != nullptr) delete tileMap[i][j];
			tileMap[i][j] = nullptr;
		}
	}
	printf("tileMap cleared\n");
}
