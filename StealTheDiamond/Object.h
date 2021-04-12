#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Level;

class Object: public sf::Drawable
{
public:
	enum Flags : unsigned int {
		MOVABLE = 1,
		DESTROYABLE = 2,
		WATER_REPLACABLE = 4,
		INTERACTIVE = 8,
		COLLECTABLE = 16
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
	virtual void onExplode();
	virtual void update();

	void removeObject(); // remove itself

	Object* getObjectAt(sf::Vector2i pos);
	int getGroundTypeAt(sf::Vector2i pos);

	bool isPositionValid(sf::Vector2i pos);
	bool isObjectAt(sf::Vector2i pos);
};

