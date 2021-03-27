#pragma once
#include <SFML/Graphics.hpp>

class Object: public sf::Drawable
{
public:
	enum Flags : unsigned int {
		MOVABLE = 1
		// add flags when needed with values of the form 2 to the power of (i)
	};

	const float size = 32.0f;

	Object(sf::Vector2i pos);

	sf::Vector2i position;
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned int flags;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

