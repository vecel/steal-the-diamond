#include "Wall.h"
#include "Object.h"
#include "Level.h"

class Level;

Wall::Wall(Level* level, sf::Vector2i pos, int id, int layer) : Object(level, pos, id, layer) {
	if (id >= 9 && id <= 16) flags = DESTROYABLE;
}
