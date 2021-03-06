#include "Player.h"
#include "Level.h"
#include <iostream> // just for debugging
#include "Wall.h"
#include "Bomb.h"

Player::Player(Level* level, sf::Vector2i pos, int id, int layer) : Object(level, pos, id, layer) {
	flags = MOVABLE | DESTROYABLE;
	bombs = 0;
}

Player::~Player() {
	printf("Player destructor\n");
}

void Player::update(double elapsed) {

	// planting active bombs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) plantBomb(sf::Vector2i(-1, 0), true);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) plantBomb(sf::Vector2i(1, 0), true);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) plantBomb(sf::Vector2i(0, -1), true);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) plantBomb(sf::Vector2i(0, 1), true);
		return;
	}

	// planting inactive bombs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) plantBomb(sf::Vector2i(-1, 0), false);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) plantBomb(sf::Vector2i(1, 0), false);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) plantBomb(sf::Vector2i(0, -1), false);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) plantBomb(sf::Vector2i(0, 1), false);
		return;
	}


	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) move(sf::Vector2i(-1, 0));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) move(sf::Vector2i(1, 0));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) move(sf::Vector2i(0, -1));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) move(sf::Vector2i(0, 1));

	if (getGroundTypeAt(position) == TileMap::WATER) onSink();
	if (getGroundTypeAt(position) == TileMap::VOID) onFallIntoVoid();
	if (getGroundTypeAt(position) == TileMap::EXIT) printf("Exit reached\n");
}

bool Player::move(sf::Vector2i dir) { 
	moved = false;

	sf::Vector2i newPos = position + dir;
	Object* nextObj = getObjectAt(newPos);
	
	if (nextObj != nullptr) {
		if (nextObj->flags & COLLECTABLE) {

			nextObj->onCollect();
			
			// simple move code
			if (!moved) {
				updatePosition(newPos);
				moved = true;
			}

			return moved;
		}

		if (nextObj->flags & INTERACTIVE) {
			nextObj->onInteract();
			return false;
		}
	}

	return Object::move(dir);
}

bool Player::onSink() {
	printf("player drowned\n");
	level->onPlayerDeath();
	level->activePlayer = nullptr;

	Object::onSink();

	return false;
}

void Player::onFallIntoVoid() {
	printf("player fell into void... sad :(\n");
	level->onPlayerDeath();
	level->activePlayer = nullptr;
	Object::onFallIntoVoid();
}

void Player::plantBomb(sf::Vector2i dir, bool active) {
	if (bombs > 0) {

		sf::Vector2i plantPos = position + dir;

		if (getObjectAt(plantPos) == nullptr) {
			//printf("planting bomb\n");
			Object* obj = new Bomb(level, plantPos, 41, 1, active);
			level->tileMap->setObjectAt(plantPos, obj);
			level->objects.push_back(obj);
			bombs--;
			// zrob porzadek z pamiecia
		}
		
	}
}


