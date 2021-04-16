#include "Door.h"
#include "Level.h"

Door::Door(Level* level, sf::Vector2i pos, int objId, int keyId, int layer) : Object(level, pos, objId, layer) {

	key = keyId;
	open = false;
	flags = INTERACTIVE;
}

Door::~Door() {

}

void Door::onInteract() {
	// sprawdz czy gracz ma klucz
	for (auto it = level->activePlayer->keys.begin(); it <
		level->activePlayer->keys.end(); ++it) {

		if (*it == key) {
			open = true;
			level->activePlayer->keys.erase(it);
			level->tileMap->setObjectAt(position, nullptr);
			level->addObjectToRemove(this);
			printf("door opened\n");
			break;
		}
	}
	printf("door onInteract\n");
}
