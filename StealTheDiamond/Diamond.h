#pragma once
#include "Object.h"
class Diamond : public Object
{
public:
	Diamond(Level* level, sf::Vector2i pos, int id, int layer = 1);
	~Diamond();

	void onCollect();
};

