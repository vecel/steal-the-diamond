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

void TileMap::setObjectAt(sf::Vector2i pos, Object* obj) {
	tileSet[pos.x + pos.y * WIDTH] = obj;
}

void TileMap::removeObjectAt(sf::Vector2i pos) {
	tileSet[pos.x + pos.y * WIDTH] = nullptr; // nullptr or empty obj
}

void TileMap::draw() {
	for (Object* obj : tileSet) if(obj != nullptr) obj->draw(*window, sf::RenderStates::Default);
}

void TileMap::clear() {
	
	printf("tileMap cleared\n");
}


Object* TileMap::operator[](sf::Vector2i pos) {
	return tileSet[pos.x + pos.y * WIDTH];
}

Object* TileMap::getObjectAt(sf::Vector2i pos) {
	return tileSet[pos.x + pos.y * WIDTH];
}

