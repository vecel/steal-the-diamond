#include <fstream>
#include <iostream>
#include "TileMap.h"
#include "Object.h"
#include "Wall.h"
#include "Player.h"

TileMap::TileMap() {
	printf("TileMap constructor\n");
}

TileMap::~TileMap() {
	printf("TileMap destructor\n");
}

void TileMap::insert(sf::Vector2i pos, Object* obj) {
	printf("TileMap insert\n");
	tileSet.insert(std::pair<sf::Vector2i, Object*>(pos, obj));
}

void TileMap::erase(sf::Vector2i pos) {
	tileSet.erase(pos);
}

void TileMap::draw() {
	for (std::map<sf::Vector2i, Object*>::iterator it = tileSet.begin();
		it != tileSet.end(); ++it) it->second->draw(*window, sf::RenderStates::Default);
}

void TileMap::clear() {
	/*for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (tileMap[i][j] != nullptr) delete tileMap[i][j];
			tileMap[i][j] = nullptr;
		}
	}*/
	printf("tileMap cleared\n");
}



void TileMap::setWindow(sf::RenderWindow* w) {
	window = w;
}



bool TileMap::Comparator::operator()(sf::Vector2i v1, sf::Vector2i v2) const {
	if (v1.y < v2.y) return true;
	else if (v1.y > v2.y) return false;
	else {
		if (v1.x < v2.x) return true;
		else return false;
	}
}

