#include "Exit.h"
#include "TileMap.h"

class TileMap;

Exit::Exit(sf::Vector2i pos, std::string txtPath) {
	if (!texture.loadFromFile(txtPath)) printf("Cannot load Exit's texture\n");

	position = pos;

	setSize(sf::Vector2f(TileMap::tileSize, TileMap::tileSize));
	setTexture(&texture);
	setPosition(sf::Vector2f(10.0f + position.x * TileMap::tileSize, 10.0f + position.y * TileMap::tileSize));

}

Exit::~Exit() {
	printf("Exit destructor\n");
}
