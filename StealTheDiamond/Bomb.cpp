#include "Bomb.h"
#include "Level.h"

Bomb::Bomb(Level* level, sf::Vector2i pos, int id, bool active) : Object(level, pos, id) {

	this->active = active;
	flags = MOVABLE | DESTROYABLE;

	if (!active) {
		flags |= COLLECTABLE;
	}
	else {
		clock.restart();
		plantTime = clock.getElapsedTime().asMilliseconds();
	}
}

Bomb::~Bomb() {

}

void Bomb::onCollect() {
	level->activePlayer->bombs++;
	removeObject();
}

void Bomb::onExplode() {
	 
	// it is important to remove bomb from its position first (but not delete) and
	// and then call onExplode function consecutive objects	
	removeObject();

	// explosion sound
	if (isObjectAt(position + sf::Vector2i(-1, -1))) getObjectAt(position + sf::Vector2i(-1, -1))->onExplode();
	if (isObjectAt(position + sf::Vector2i(0, -1))) getObjectAt(position + sf::Vector2i(0, -1))->onExplode();
	if (isObjectAt(position + sf::Vector2i(1, -1))) getObjectAt(position + sf::Vector2i(1, -1))->onExplode();
	if (isObjectAt(position + sf::Vector2i(-1, 0))) getObjectAt(position + sf::Vector2i(-1, 0))->onExplode();
	if (isObjectAt(position + sf::Vector2i(1, 0))) getObjectAt(position + sf::Vector2i(1, 0))->onExplode();
	if (isObjectAt(position + sf::Vector2i(-1, 1))) getObjectAt(position + sf::Vector2i(-1, 1))->onExplode();
	if (isObjectAt(position + sf::Vector2i(0, 1))) getObjectAt(position + sf::Vector2i(0, 1))->onExplode();
	if (isObjectAt(position + sf::Vector2i(1, 1))) getObjectAt(position + sf::Vector2i(1, 1))->onExplode();

	printf("Bomb exploded\n");
}

void Bomb::update() {
	if (active) {
		if (clock.getElapsedTime().asMilliseconds() - plantTime >= 3000) onExplode(); // explode after 3 sec
	}
}
