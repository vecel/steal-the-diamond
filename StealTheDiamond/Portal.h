#pragma once
#include "Object.h"

class Portal : public Object
{
public:
	Portal(Level* level, sf::Vector2i pos, int id, sf::Vector2i destination, int layer = 0);
	~Portal();

	void onInteract();
	void update(double elapsed);

	sf::Vector2i destination;
};

