#pragma once
#include "Object.h"
class Bomb : public Object
{
public:
	Bomb(Level* level, sf::Vector2i pos, int id, bool active = false);
	~Bomb();

	void onCollect();
	void onExplode();

	void update();

	bool active;
	float plantTime;
	sf::Clock clock;
};

