#include "Diamond.h"
#include "Level.h"

Diamond::Diamond(Level* level, sf::Vector2i pos, int id) : Object(level, pos, id) {

	if (!texture.loadFromFile("textures\\diamond.png")) {
		printf("Cannot load diamond texture\n");
	}
	sprite.setTexture(texture);

	flags = MOVABLE | COLLECTABLE | DESTROYABLE;
}

Diamond::~Diamond() {
	printf("Diamond destructor\n");
}

void Diamond::onCollect() {
	printf("diamond collected\n");
	
	level->diamonds++;
	std::cout << level->diamonds << '\n';
	level->tileMap->removeObjectAt(position);
	level->addObjectToRemove(this);

	// zamiast porownania moze funkcja w level.cpp isLevelWon()
	if (level->diamonds == level->diamondsToCollect) {
		printf("All diamonds collected\n");
		level->tileMap->showExit();
	}
}
