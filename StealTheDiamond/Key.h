#pragma once
#include "Object.h"

class Key : public Object
{
public:
	Key(Level* level, sf::Vector2i pos, int id);
	~Key();

	void onCollect();

	int getId();

private:
	int keyId;
};
