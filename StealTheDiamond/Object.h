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

	Object(Level* l, sf::Vector2i pos, int objId, int layer);
	virtual ~Object() = 0;

	//void setTextureRect(const sf::IntRect& rectangle);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual bool move(sf::Vector2i dir);
	virtual bool onSink();
	virtual void onFallIntoVoid();
	virtual void onCollect();
	virtual void onInteract();
	virtual void onExplode();
	virtual void update(double elapsed);

	Level* level;
	sf::Vector2i position;
	int layer;
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned int flags;
	bool moved;

	void removeObject(); // remove itself

	Object* getObjectAt(sf::Vector2i pos, int layer = 1);
	int getGroundTypeAt(sf::Vector2i pos);
	double getElapsedTime();

	bool isPositionValid(sf::Vector2i pos);
	bool isObjectAt(sf::Vector2i pos, int layer = 1);
};

