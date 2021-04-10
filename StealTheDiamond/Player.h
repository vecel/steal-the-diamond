#pragma once
#include "Object.h"
#include <iostream>

class Level;

class Player : public Object
{
public:
	Player(Level* level, sf::Vector2i pos, int id);
	~Player();

	void update();

	bool move(sf::Vector2i dir);
	bool onSink();
	void onFallIntoVoid();

	sf::Vector2i velocity;
	std::vector<int> keys;
};

