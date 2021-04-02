#include "Level.h"
#include <fstream>
#include <iostream>
#include "Wall.h"
#include "Player.h"

Level::Level(sf::RenderWindow* window, std::string filePath) {
	tileMap = new TileMap(window);
	loadFromFile(filePath);
}

Level::~Level() {

}

void Level::loadFromFile(std::string path) {
	printf("loadFromFile\n");
	std::fstream levelData(path);
	for (int i = 0; i < tileMap->HEIGHT; ++i) {
		for (int j = 0; j < tileMap->WIDTH; ++j) {
			std::string objType;
			levelData >> objType;

			sf::Vector2i position(j, i);

			if (objType == "Wall") {
				//printf("Wall\n");
				Object* obj = new Wall(this, position);
				objects.push_back(obj);
				tileMap->setObjectAt(position, obj);
			}
			else if (objType == "Player") {
				//printf("Player\n");
				Object* obj = new Player(this, position);
				activePlayer = dynamic_cast<Player*>(obj);
				objects.push_back(obj);
				tileMap->setObjectAt(position, obj);
			}
			// TODO EmptyTile
		}
	}
	levelData.close();
}

void Level::draw() { tileMap->draw(); }

