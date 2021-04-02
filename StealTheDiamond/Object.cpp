#include "Object.h"
#include "Level.h"

#include <iostream>

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

void Object::move(sf::Vector2i dir){

}

Object* Object::getObjectAt(sf::Vector2i pos) {
	return level->tileMap->getObjectAt(pos);
}
