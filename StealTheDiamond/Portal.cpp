#include "Portal.h"
#include "Level.h"

Portal::Portal(Level* level, sf::Vector2i pos, int id, sf::Vector2i destination, int layer) : Object(level, pos, id, layer) {
	this->destination = destination;
	lastUse = 0.0;
	inactiveTime = 1000;
	type = static_cast<PortalType>(id - 100);
	printf("Portal type %d\n", type);

}

Portal::~Portal() {

}

void Portal::onRender() {
	//setUpAnimation();
}

void Portal::update(double elapsed) {
	// update animation
	//animation->update(std::fmod(elapsed, animation->getLength())); 

	// set portal inactive for 1 second after teleporting something
	if (elapsed - lastUse >= inactiveTime) {
		// check if there is object in portal (same position, layer up)
		if (getObjectAt(position) != nullptr) onInteract(elapsed);
	}

}

void Portal::onInteract(double elapsed) {

	if (getObjectAt(destination) == nullptr) {
		Object* obj = getObjectAt(position);

		bool teleport = false;

		if		(type == PortalType::DEFAULT) teleport = true;
		else if (type == PortalType::PLAYER_ONLY && dynamic_cast<Player*>(obj) != nullptr) { teleport = true; printf("Player in player portal\n"); }
		else if (type == PortalType::OBJECTS_ONLY && dynamic_cast<Player*>(obj) == nullptr) { teleport = true; printf("Object in object portal\n"); }
		
		if (teleport) {
			obj->updatePosition(destination);
			printf("Teleported\n");
			// play sound
		}
		
	}
	else {
		printf("Destination position occupied\n");
		lastUse = elapsed;
		// play sound
	}
}

void Portal::setUpAnimation() {
	sf::Vector2i initialTxtPix;

	switch (type) {
	case PortalType::DEFAULT: initialTxtPix = sf::Vector2i(0, 0); break;
	case PortalType::PLAYER_ONLY: initialTxtPix = sf::Vector2i(4 * 32, 0); break;
	case PortalType::OBJECTS_ONLY: initialTxtPix = sf::Vector2i(0, 32); break;
	}

	printf("InitialTxtPix %d %d\n", initialTxtPix.x, initialTxtPix.y);

	sf::IntRect txtRect(initialTxtPix, sf::Vector2i(32, 32));
	
	animation = new Animation(this);
	animation->addFrame({ sf::IntRect(initialTxtPix.x, initialTxtPix.y, 32, 32), 250.0 });
	animation->addFrame({ sf::IntRect(initialTxtPix.x + 32, initialTxtPix.y, 32, 32), 250.0 });
	animation->addFrame({ sf::IntRect(initialTxtPix.x + 64, initialTxtPix.y, 32, 32), 250.0 });
	animation->addFrame({ sf::IntRect(initialTxtPix.x + 96, initialTxtPix.y, 32, 32), 250.0 });
}
