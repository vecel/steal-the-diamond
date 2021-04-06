#pragma once
#include "Object.h"
#include <iostream>

class Level;

class Player : public Object
{
public:
	Player(Level* level, sf::Vector2i pos);
	~Player();

	void update();

	bool move(sf::Vector2i dir);
	bool onSinking();

	sf::Vector2i velocity;
};

