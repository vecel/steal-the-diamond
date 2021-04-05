#include "Player.h"
#include "Level.h"
#include <iostream> // just for debugging
#include "Wall.h"

Player::Player(Level* level, sf::Vector2i pos) : Object(level, pos) {
	
	// create and load the texture
	if (!texture.loadFromFile("textures\\player.png")) {
		printf("Cannot load the texture\n");
	}
	sprite.setTexture(texture);

	flags = MOVABLE;
}

bool Player::move(sf::Vector2i dir) {
	/* for the moment player's move function is the same as object's move function*/

	sf::Vector2i newPos = position + dir;
	Object* nextObj = getObjectAt(newPos);

	if (nextObj == nullptr) {
		// if object at newPos is movable then call it's move method with the same dir parameter
		if (!moved) {
			level->tileMap->setObjectAt(newPos, this);
			level->tileMap->removeObjectAt(position);
			position = newPos;
			sprite.setPosition(sf::Vector2f(10.0f + size * position.x, 10.0f + size * position.y));
			//moved = true;
		}
	}
	else if (nextObj->flags & MOVABLE) {
		printf("movable object pla\n");
		if (!nextObj->move(dir)) move(dir);
	}
	
	return moved;
}

