#pragma once
#include "Object.h"
#include "Animation.h"

class Portal : public Object
{
public:
	enum class PortalType {
		DEFAULT = 0,
		PLAYER_ONLY = 1,
		OBJECTS_ONLY = 2
	};

	Portal(Level* level, sf::Vector2i pos, int id, sf::Vector2i destination, int layer = 0);
	~Portal();

	void onRender();

	void update(double elapsed);
	void onInteract(double elapsed); // not inherited from Object

	void setUpAnimation();

	double lastUse;
	double inactiveTime;
	sf::Vector2i destination;
	PortalType type;
	Animation* animation;
};

