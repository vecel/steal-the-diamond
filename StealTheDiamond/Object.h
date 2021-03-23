#pragma once

#include <SFML/Graphics.hpp>

// store flags
enum Flags : unsigned int {
	MOVABLE = 1
	// add flags when needed with values of the form 2 to the power of (i)
};

class Object: public sf::Drawable
{
public:
	int x, y;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

