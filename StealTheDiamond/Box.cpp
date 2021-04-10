#include "Box.h"
#include "Level.h"

Box::Box(Level* level, sf::Vector2i pos, int id) : Object(level, pos, id){

	flags = MOVABLE | WATER_REPLACABLE;
}

Box::~Box() {
	printf("Box destructor\n");
}
