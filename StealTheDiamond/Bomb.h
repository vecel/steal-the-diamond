#pragma once
#include "Object.h"
#include "Animation.h"

class Bomb : public Object
{
public:
	Bomb(Level* level, sf::Vector2i pos, int id, bool active = false);
	~Bomb();

	void onCollect();
	void onExplode();

	void update(double elapsed);

	double explosionTime = 2000.0;
	bool active;
	float plantTime;
	Animation* animation;
};

