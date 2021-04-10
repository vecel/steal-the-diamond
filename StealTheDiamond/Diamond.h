#pragma once
#include "Object.h"
class Diamond : public Object
{
public:
	Diamond(Level* level, sf::Vector2i pos, int id);
	~Diamond();

	void onCollect();
};

