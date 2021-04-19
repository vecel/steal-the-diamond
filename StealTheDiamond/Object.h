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

	static int size;
	static sf::Vector2f transform; 

	Object(Level* l, sf::Vector2i pos, int objId, int layer);
	virtual ~Object() = 0;

	virtual void onRender();
	
	virtual void update(double elapsed);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual bool move(sf::Vector2i dir);
	virtual bool onSink();
	virtual void onFallIntoVoid();
	virtual void onCollect();
	virtual void onInteract();
	virtual void onExplode();

	Level* level;
	sf::Vector2i position;
	int layer;
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned int flags;
	bool moved;

	void removeObject(); // remove itself

	/* 
		moves object to given position 
	*/
	void updatePosition(sf::Vector2i pos); // test

	Object* getObjectAt(sf::Vector2i pos, int layer = 1);
	int getGroundTypeAt(sf::Vector2i pos);
	double getElapsedTime();

	bool isPositionValid(sf::Vector2i pos);
	bool isObjectAt(sf::Vector2i pos, int layer = 1);
};

