#include "Diamond.h"
#include "Level.h"

Diamond::Diamond(Level* level, sf::Vector2i pos) : Object(level, pos) {

	if (!texture.loadFromFile("textures\\diamond.png")) {
		printf("Cannot load diamond texture\n");
	}
	sprite.setTexture(texture);

	flags = MOVABLE | COLLECTABLE | DROWNING;
}

Diamond::~Diamond() {
	printf("Diamond destructor\n");
}

void Diamond::onCollect() {
	level->diamonds++;
	printf("diamond collected\n");
	std::cout << level->diamonds << '\n';
	level->addObjectToRemove(this);

	// zamiast porownania moze funkcja w level.cpp isLevelWon()
	if (level->diamonds == level->diamondsToCollect) {
		printf("All diamonds collected\n");
		level->tileMap->showExit();
	}
}