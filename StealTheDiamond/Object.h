#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Level;

class Object: public sf::Drawable
{
public:
	enum Flags : unsigned int {
		MOVABLE = 1,
		WATER_REPLACABLE = 2,
		INTERACTIVE = 4,
		COLLECTABLE = 8
		// add flags when needed with values of the form 2 to the power of (i)
	};

	/*static*/ const float size = 32.0f;

	Object(Level* l, sf::Vector2i pos, int objId);
	virtual ~Object() = 0;

	Level* level;
	sf::Vector2i position;
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned int flags;
	bool moved;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual bool move(sf::Vector2i dir);
	virtual bool onSink();
	virtual void onFallIntoVoid();
	virtual void onCollect();
	virtual void onInteract();

protected:
	Object* getObjectAt(sf::Vector2i pos);

	int getGroundTypeAt(sf::Vector2i pos);
};

