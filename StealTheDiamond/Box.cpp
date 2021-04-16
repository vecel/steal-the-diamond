#include "Box.h"
#include "Level.h"

Box::Box(Level* level, sf::Vector2i pos, int id, int layer) : Object(level, pos, id, layer){

	flags = MOVABLE | WATER_REPLACABLE | DESTROYABLE;
}

Box::~Box() {
	printf("Box destructor\n");
}
