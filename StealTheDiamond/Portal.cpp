#include "Portal.h"
#include "Level.h"

Portal::Portal(Level* level, sf::Vector2i pos, int id, sf::Vector2i destination, int layer) : Object(level, pos, id, layer) {
	this->destination = destination;
}

Portal::~Portal() {

}

void Portal::onInteract() {
	if (getObjectAt(destination) == nullptr) {
		Object* obj = getObjectAt(position);
		obj->setPosition(destination);
		printf("Teleported\n");
	}
	else {
		printf("Destination position occupied\n");
		// play sound
	}
}

void Portal::update(double elapsed) {
	// check if there is object in portal (same position, layer up)
	if (getObjectAt(position) != nullptr) onInteract();

	// idea: set portal inactive for 1 second after teleporting something
}
