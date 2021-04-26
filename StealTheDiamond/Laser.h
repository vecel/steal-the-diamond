#pragma once
#include "Object.h"

class Laser : public Object
{
public:
	static enum class Facing
	{
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};

	static int defaultId;

	Laser(Level* level, sf::Vector2i pos, int id, int layer = 1);
	~Laser();

	void onRender();

	void update(double elapsed);

	void renderLaserBeam();

	Facing facing;
	sf::Vector2i facingVector;
	sf::Texture beamTexture;

private:
	void setFacing(int laserId);
};

