#include "Box.h"

Box::Box(Level* level, sf::Vector2i pos) : Object(level, pos){

	if (!texture.loadFromFile("textures\\wooden-box.png")) {
		printf("Cannot load texture\n");
	}
	sprite.setTexture(texture);

	flags = MOVABLE | WATER_REPLACABLE;
}

Box::~Box() {

}
