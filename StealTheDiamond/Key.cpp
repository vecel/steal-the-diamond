#include "Key.h"
#include "Level.h"

Key::Key(Level* level, sf::Vector2i pos, int id, int keyId) : Object(level, pos, -1) {

	if (!texture.loadFromFile("textures\\keys.png", sf::IntRect(0, 0, 32, 32))) printf("Cannot load key texture\n");
	sprite.setTexture(texture);

	flags = MOVABLE | COLLECTABLE;
	this->keyId = keyId;
}

Key::~Key() {
	printf("Key destructor\n");
}

void Key::onCollect() {
	printf("key collected\n");
	level->activePlayer->keys.push_back(keyId);
	level->tileMap->removeObjectAt(position);
	level->addObjectToRemove(this);
}

int Key::getId() { 
	return keyId; 
}
