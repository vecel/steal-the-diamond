#include "Object.h"
#include "Level.h"
#include "TileMap.h"

#include <iostream>

class TileMap;

float Object::size = 32.0f;
sf::Vector2f Object::transform(10.0f, 10.0f);

Object::Object(Level* l, sf::Vector2i pos, int objId, int layer) {
	position = pos;
	this->layer = layer;
	level = l;
	moved = false;
	sprite.setPosition(sf::Vector2f(10.0f + size * position.x, 10.0f + size * position.y));

	if (objId != -1) {
		sf::Vector2i txtPix = level->getTextureStartingPoint(objId);
		sf::IntRect txtRect(txtPix, sf::Vector2i(size, size));

		if (objId < 100) {
			if (!texture.loadFromFile("textures\\object-assets.png", txtRect)) printf("Cannot load texture\n");
		}
		else if (objId >= 100) {
			if (!texture.loadFromFile("textures\\object-0-assets.png", txtRect)) printf("Cannot load texture\n");
		}

		sprite.setTexture(texture);
	}
}

Object::~Object()
{

}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->sprite, states);
}

bool Object::move(sf::Vector2i dir){
	moved = false;

	sf::Vector2i newPos = position + dir;
	Object* nextObj = getObjectAt(newPos);

	if (nextObj == nullptr) {
		// if object at newPos is movable then call it's move method with the same dir parameter
		if (!moved) {
			
			setPosition(newPos);
			moved = true;
		}
	}
	else if (nextObj->flags & MOVABLE) {
		printf("movable object obj\n");
		if (nextObj->move(dir)) move(dir);
	}

	if (getGroundTypeAt(position) == TileMap::WATER) {
		onSink();
		return true;
	}

	if (getGroundTypeAt(position) == TileMap::VOID) {
		onFallIntoVoid();
		return true;
	}

	return moved;
}

bool Object::onSink() {
	if (flags & WATER_REPLACABLE) {
		level->tileMap->fillWater(position);
		level->tileMap->setObjectAt(position, nullptr);
		level->addObjectToRemove(this);
		return false;
	}
	else {
		printf("drowned\n");
		removeObject();
		return false;
	}
}

void Object::onFallIntoVoid() {
	removeObject();
}

void Object::onCollect() {
}

void Object::onInteract() {

}

void Object::onExplode() {
	if (flags & DESTROYABLE) {
		removeObject();
	}
}

void Object::update(double elapsed) {

}

void Object::removeObject() {
	level->tileMap->removeObjectAt(position);
	level->addObjectToRemove(this);
}

void Object::setPosition(sf::Vector2i pos) {
	level->tileMap->setObjectAt(pos, this);
	level->tileMap->removeObjectAt(position);
	position = pos;
	sprite.setPosition(transform.x + size * position.x, transform.y + size * position.y);
}

Object* Object::getObjectAt(sf::Vector2i pos, int layer) {
	return level->tileMap->getObjectAt(pos, layer);
}

int Object::getGroundTypeAt(sf::Vector2i pos) {
	return level->tileMap->getGroundTypeAt(pos);
}

double Object::getElapsedTime() {
	return level->clock.getElapsedTime().asMilliseconds();
}

bool Object::isPositionValid(sf::Vector2i pos) {
	int index = pos.x + pos.y * TileMap::WIDTH;
	return index >= 0 && index < TileMap::WIDTH * TileMap::HEIGHT;
}

bool Object::isObjectAt(sf::Vector2i pos, int layer) {
	if (!isPositionValid(pos)) return false;
	return getObjectAt(pos, layer) != nullptr;
}
