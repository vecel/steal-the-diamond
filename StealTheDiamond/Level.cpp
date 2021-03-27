#include "Level.h"
#include <fstream>
#include <iostream>
#include "Wall.h"

Level::Level(sf::RenderWindow* w, std::string filePath) {
	tileMap.setWindow(w);
	loadFromFile(filePath);
}

Level::~Level() {

}

void Level::loadFromFile(std::string path) {
	printf("loadFromFile\n");
	std::fstream levelData(path);
	for (int i = 0; i < tileMap.HEIGHT; ++i) {
		for (int j = 0; j < tileMap.WIDTH; ++j) {
			std::string objType;
			levelData >> objType;

			sf::Vector2i position(j, i);

			if (objType == "Wall") {
				printf("Wall\n");
				Object* obj = new Wall(position);
				objects.push_back(obj);
				tileMap.insert(position, obj);
			}
			// TODO Player, Empty
		}
	}
	levelData.close();
}

void Level::draw() { tileMap.draw(); }
