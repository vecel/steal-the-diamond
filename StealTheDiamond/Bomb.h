#pragma once
#include "Object.h"
#include "Animation.h"

class Bomb : public Object
{
public:
	Bomb(Level* level, sf::Vector2i pos, int id, int layer = 1, bool active = false);
	~Bomb();

	void update(double elapsed);

	void onCollect();
	void onExplode();

	void setUpAnimation();

	double explosionTime = 2000.0;
	bool active;
	float plantTime;
	Animation* animation;
};

