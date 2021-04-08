#include "Key.h"
#include "Level.h"

Key::Key(Level* level, sf::Vector2i pos, int id) : Object(level, pos) {

	if (!texture.loadFromFile("textures\\keys.png", sf::IntRect(0, 0, 32, 32))) printf("Cannot load key texture\n");
	sprite.setTexture(texture);

	flags = MOVABLE | COLLECTABLE;
	keyId = id;
}

Key::~Key() {
	printf("Key destructor\n");
}

void Key::onCollect() {
	printf("key collected\n");
	level->activePlayer->keys.push_back(keyId);
	level->addObjectToRemove(this);
}

int Key::getId() { 
	return keyId; 
}
