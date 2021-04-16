#pragma once
#include "Object.h"

class Door : public Object
{
public:
	Door(Level* level, sf::Vector2i pos, int objId, int keyId, int layer = 1);
	~Door();

	void onInteract();

private:
	int key;
	bool open;
};

