#pragma once
#include "Object.h"
#include "Level.h"

class Box : public Object
{
public:
	Box(Level* level, sf::Vector2i pos);
	~Box();
};

