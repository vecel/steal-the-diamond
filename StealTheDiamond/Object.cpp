#include "Object.h"

Object::Object(sf::Vector2i pos) {
	position = pos;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->sprite, states);
}


