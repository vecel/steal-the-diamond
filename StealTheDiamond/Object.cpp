#include "Object.h"
#include "Level.h"
#include "TileMap.h"

#include <iostream>

class TileMap;

Object::Object(Level* l, sf::Vector2i pos) {
	position = pos;
	level = l;
	moved = false;
	sprite.setPosition(sf::Vector2f(10.0f + size * position.x, 10.0f + size * position.y));
}

Object::~Object()
{

}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->sprite, states);
}

bool Object::move(sf::Vector2i dir){
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
		printf("movable object obj\n");
		if (!nextObj->move(dir)) move(dir);
		
	}

	if (level->tileMap->getGroundTypeAt(position) == TileMap::WATER) {
		if (flags & WATER_REPLACABLE) {
			level->tileMap->fillWater(position);
			level->tileMap->setObjectAt(position, nullptr);
		}
	}

	return moved;
}

Object* Object::getObjectAt(sf::Vector2i pos) {
	return level->tileMap->getObjectAt(pos);
}
