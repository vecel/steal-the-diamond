#include "Diamond.h"
#include "Level.h"

Diamond::Diamond(Level* level, sf::Vector2i pos) : Object(level, pos) {

	if (!texture.loadFromFile("textures\\diamond.png")) {
		printf("Cannot load diamond texture\n");
	}
	sprite.setTexture(texture);

	flags = MOVABLE | COLLECTABLE;
}

Diamond::~Diamond() {
	printf("Diamond destructor\n");
}

void Diamond::onCollect() {
	level->diamonds++;
	printf("diamond collected\n");
	std::cout << level->diamonds << '\n';
	level->addObjectToRemove(this);
}
