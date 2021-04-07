#include "Player.h"
#include "Level.h"
#include <iostream> // just for debugging
#include "Wall.h"

Player::Player(Level* level, sf::Vector2i pos) : Object(level, pos) {
	
	// create and load the texture
	if (!texture.loadFromFile("textures\\player-yellow.png")) {
		printf("Cannot load the texture\n");
	}
	sprite.setTexture(texture);

	flags = MOVABLE | DROWNING;
}

Player::~Player() {
	printf("Player destructor\n");
}

void Player::update() {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) move(sf::Vector2i(-1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) move(sf::Vector2i(1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) move(sf::Vector2i(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) move(sf::Vector2i(0, 1));

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
				level->tileMap->setObjectAt(newPos, this);
				level->tileMap->removeObjectAt(position);
				position = newPos;
				sprite.setPosition(sf::Vector2f(10.0f + size * position.x, 10.0f + size * position.y));
				moved = true;
			}

			return moved;
		}
	}

	return Object::move(dir);
}

bool Player::onSink() {
	printf("player drowned\n");

	level->activePlayer = nullptr;

	Object::onSink();

	return false;
}

void Player::onFallIntoVoid() {
	printf("player fell into void... sad :(\n");
	level->activePlayer = nullptr;
	Object::onFallIntoVoid();
}

