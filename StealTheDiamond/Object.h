#pragma once
#include <SFML/Graphics.hpp>

class Level;

class Object: public sf::Drawable
{
public:
	enum Flags : unsigned int {
		MOVABLE = 1
		// add flags when needed with values of the form 2 to the power of (i)
	};

	const float size = 32.0f;

	Object(Level* l, sf::Vector2i pos);
	virtual ~Object() = 0;

	Level* level;
	sf::Vector2i position;
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned int flags;
	bool moved;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void move(sf::Vector2i dir);

protected:
	Object* getObjectAt(sf::Vector2i pos);
};

