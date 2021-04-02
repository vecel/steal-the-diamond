#include "Player.h"
#include "Level.h"
#include <iostream>
#include "Wall.h"

Player::Player(Level* level, sf::Vector2i pos) : Object(level, pos) {
	
	// create and load the texture
	if (!texture.loadFromFile("textures\\player.png")) {
		printf("Cannot load the texture\n");
	}
	sprite.setTexture(texture);

	flags = MOVABLE;
}

void Player::move(sf::Vector2i dir) {
	sf::Vector2i newPos = position + dir;

	if (getObjectAt(newPos) == nullptr && !moved /*lub movable*/) {
		printf("move\n");
		level->tileMap->setObjectAt(newPos, this);
		level->tileMap->removeObjectAt(position);
		position = newPos;
		moved = true;
	}

	sprite.setPosition(sf::Vector2f(10.0f + size * position.x, 10.0f + size * position.y));
}

