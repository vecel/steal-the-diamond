#include "Level.h"
#include <fstream>
#include <iostream>
#include "Wall.h"
#include "Player.h"
#include "Box.h"
#include "Diamond.h"

Level::Level(sf::RenderWindow* window, std::string filePath) {
	tileMap = new TileMap(window, "textures\\ground-assets.png");

	loadFromFile(filePath);

	diamonds = 0;
}

Level::~Level() {

}

void Level::loadFromFile(std::string path) {
	printf("loadFromFile\n");

	std::fstream levelData(path);

	if (!levelData.good()) throw "Unexpected problem with level data file";

	levelData.ignore(1000, ':'); // ignore descriptions in level data file
	levelData >> diamondsToCollect;

	tileMap->loadLayer0(levelData);

	for (int i = 0; i < tileMap->HEIGHT; ++i) {
		for (int j = 0; j < tileMap->WIDTH; ++j) {
			std::string objType;
			levelData >> objType;

			sf::Vector2i position(j, i);

			if (objType == "Wall") {
				//printf("Wall\n");
				Object* obj = new Wall(this, position);
				objects.push_back(obj);
			}
			else if (objType == "Player") {
				//printf("Player\n");
				Object* obj = new Player(this, position);
				activePlayer = dynamic_cast<Player*>(obj);
				objects.push_back(obj);
			}
			else if (objType == "Box") {
				Object* obj = new Box(this, position);
				objects.push_back(obj);
			}
			else if (objType == "Diam") {
				Object* obj = new Diamond(this, position);
				objects.push_back(obj);
			}
		}
	}

	tileMap->loadLayer1(objects);

	levelData.close();
}

void Level::draw() { tileMap->draw(); }

void Level::addObjectToRemove(Object* obj) {
	objToRemove.push_back(obj);
}

void Level::removeOldObj() {
	for (std::vector<Object*>::iterator it = objToRemove.begin();
		it < objToRemove.end(); ++it) {

		for (auto iter = objects.begin(); iter < objects.end(); iter++) {
			if (*it == *iter) {
				objects.erase(iter);
				printf("object erased\n");
				break;
			}
		}

	}
}

