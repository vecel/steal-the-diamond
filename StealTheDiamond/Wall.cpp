#include "Wall.h"
#include "Object.h"

Wall::Wall(sf::Vector2i pos) : Object(pos) {
	
	
	if (!texture.loadFromFile("textures\\wall-test.png")) {
		printf("Cannot load the texture\n");
	}
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(10.0f + size * position.x, 10.0f + size * position.y));
}
