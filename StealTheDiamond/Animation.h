#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class Animation
{
	struct Frame
	{
		sf::IntRect frameRect;
		double duration;
	};

public:
	Animation(Object* target);
	~Animation();
	void addFrame(Frame&& frame);
	void update(double elapsedTime);
	double getLength();

private:
	std::vector<Frame> frames;
	double totalLength;
	double progress;
	Object* target;
};

