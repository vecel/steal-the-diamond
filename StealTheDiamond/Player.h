#pragma once
#include "Object.h"

class Level;

class Player : public Object
{
public:
	Player(Level* level, sf::Vector2i pos);
	void move(sf::Vector2i dir);

private:
	
};

