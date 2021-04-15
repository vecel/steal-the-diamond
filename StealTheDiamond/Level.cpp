#include "Level.h"
#include <fstream>
#include <iostream>
#include "Wall.h"
#include "Player.h"
#include "Box.h"
#include "Diamond.h"
#include "Key.h"
#include "Door.h"
#include "Bomb.h"

const float Level::tileSize = 32.0f;

Level::Level(sf::RenderWindow* window, std::string filePath) {
	tileMap = new TileMap(window, "textures\\ground-assets.png");
	clock.restart();

	setUpObjectTextures();
	loadFromFile(filePath);

	diamonds = 0;
}

Level::~Level() {

}

void Level::loadFromFile(std::string path) {
	printf("loadFromFile\n");

	std::fstream levelData(path);

	if (!levelData.good()) throw "Unexpected problem with level data file";

	if (levelData.is_open()) {

		levelData.ignore(1000, ':'); // ignore descriptions in level data file
		levelData >> diamondsToCollect;

		tileMap->loadLayer0(levelData);

		loadObjects(levelData);

		tileMap->loadLayer1(objects);

	}

	levelData.close();
}

void Level::draw() { tileMap->draw(); }

void Level::updateLevel() {
	double elapsed = clock.getElapsedTime().asMilliseconds();
	for (Object* obj : objects) if (obj != nullptr) obj->update(elapsed);
	removeOldObj();
}

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

sf::Vector2i Level::getTextureStartingPoint(int id) {
	return objectTextures[id];
}




void Level::setUpObjectTextures() {
	int txtCount = 128;
	objectTextures.resize(txtCount);

	// objectTextures[0] - there is no texture for empty object
	objectTextures[1] = sf::Vector2i(0, 0); // simple wall
	objectTextures[2] = sf::Vector2i(tileSize, 0); // dragon relief
	objectTextures[3] = sf::Vector2i(2 * tileSize, 0); // stone wall
	objectTextures[8] = sf::Vector2i(7 * tileSize, 0); // snowy wall
	objectTextures[9] = sf::Vector2i(0, tileSize); // broken wall
	objectTextures[11] = sf::Vector2i(2 * tileSize, tileSize); // broken stone wall
	objectTextures[16] = sf::Vector2i(7 * tileSize, tileSize); // broken snowy wall
	objectTextures[17] = sf::Vector2i(0, 2 * tileSize); // box
	objectTextures[21] = sf::Vector2i(4 * tileSize, 2 * tileSize);
	objectTextures[33] = sf::Vector2i(0, 4 * tileSize);
	objectTextures[41] = sf::Vector2i(0, 5 * tileSize); // bomb
	objectTextures[42] = sf::Vector2i(tileSize, 5 * tileSize); // active bomb

	objectTextures[99] = sf::Vector2i(tileSize, tileSize); // temporary blank tile
}

void Level::loadObjects(std::fstream& levelData) {
	for (int i = 0; i < tileMap->HEIGHT; ++i) {
		for (int j = 0; j < tileMap->WIDTH; ++j) {
			int objId;
			levelData >> objId;

			sf::Vector2i position(j, i);

			if (objId > 0 && objId <= 16) {
				Object* obj = new Wall(this, position, objId);
				objects.push_back(obj);
			}
			else if (objId > 16 && objId <= 17) {
				Object* obj = new Box(this, position, objId);
				objects.push_back(obj);
			}
			else if (objId > 20 && objId <= 24) {
				Object* obj = new Player(this, position, objId);
				activePlayer = dynamic_cast<Player*>(obj);
				objects.push_back(obj);
			}
			else if (objId > 24 && objId <= 32) {
				Object* obj = new Key(this, position, objId, 1);
				objects.push_back(obj);
			}
			else if (objId > 32 && objId <= 40) {
				Object* obj = new Door(this, position, objId, 1);
				objects.push_back(obj);
			}
			else if (objId == 41) {
				Object* obj = new Bomb(this, position, objId);
				objects.push_back(obj);
			}
			else if (objId == 99) {
				Object* obj = new Diamond(this, position, objId);
				objects.push_back(obj);
			}
			
		}
	}
}

