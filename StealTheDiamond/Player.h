#pragma once
#include "Object.h"
#include <iostream>

class Level;

class Player : public Object
{
public:
	Player(Level* level, sf::Vector2i pos, int id, int layer = 1);
	~Player();

	bool move(sf::Vector2i dir);
	bool onSink();
	void onFallIntoVoid();
	void update(double elapsed);

	void plantBomb(sf::Vector2i dir, bool active);

	sf::Vector2i velocity;
	std::vector<int> keys;
	int bombs;

private:
	void showProperties(); // for debug
};

