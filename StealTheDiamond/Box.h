#pragma once
#include "Object.h"
#include "Level.h"

class Box : public Object
{
public:
	Box(Level* level, sf::Vector2i pos, int id, int layer = 1);
	~Box();
};

