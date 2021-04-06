#include "Level.h"
#include <fstream>
#include <iostream>
#include "Wall.h"
#include "Player.h"
#include "Box.h"

Level::Level(sf::RenderWindow* window, std::string filePath) {
	tileMap = new TileMap(window);
	loadFromFile(filePath);
}

Level::~Level() {

}

void Level::loadFromFile(std::string path) {
	printf("loadFromFile\n");

	std::fstream levelData(path);

	tileMap->loadLayer0(levelData, "textures\\ground-assets.png");

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
		}
	}

	tileMap->loadLayer1(objects);

	levelData.close();
}

void Level::draw() { tileMap->draw(); }

void Level::addObjectToRemove(Object* obj) {
	/*for (std::vector<Object*>::iterator it = objects.begin(); 
		it < objects.end(); ++it) {

		if (*it == obj) {
			printf("pointers match\n");
			//objects.erase(it);
			printf("after erase\n");
		}

	}*/
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

