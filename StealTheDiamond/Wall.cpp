#include "Wall.h"
#include "Object.h"

Wall::Wall(Level* level, sf::Vector2i pos) : Object(level, pos) {
	
	
	if (!texture.loadFromFile("textures\\stone-wall.png")) {
		printf("Cannot load the texture\n");
	}
	sprite.setTexture(texture);
	
}
