#include "Bomb.h"
#include "Level.h"

Bomb::Bomb(Level* level, sf::Vector2i pos, int id, int layer, bool active) : Object(level, pos, id, layer) {

	this->active = active;
	flags = MOVABLE | DESTROYABLE;

	if (!active) {
		flags |= COLLECTABLE;
	}
	else {
		plantTime = getElapsedTime();

		if (!texture.loadFromFile("textures\\bomb-anim.png")) printf("Cannot load bomb animation texture\n");
		sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

		animation = new Animation(this);

		animation->addFrame({ sf::IntRect(0, 0, 32, 32), 500.0 });
		animation->addFrame({ sf::IntRect(32, 0, 32, 32), 500.0 });
		animation->addFrame({ sf::IntRect(64, 0, 32, 32), 500.0 });
		animation->addFrame({ sf::IntRect(96, 0, 32, 32), 500.0 });
	}
}

Bomb::~Bomb() {

}

void Bomb::onCollect() {
	level->activePlayer->bombs++;
	removeObject();
}

void Bomb::onExplode() {
	 
	// it is important to remove bomb from its position first (but not delete) and
	// and then call onExplode function consecutive objects	to avoid infinite recursion
	removeObject();

	// add explosion sound

	if (isObjectAt(position + sf::Vector2i(-1, -1), 1)) getObjectAt(position + sf::Vector2i(-1, -1), 1)->onExplode();
	if (isObjectAt(position + sf::Vector2i( 0, -1), 1)) getObjectAt(position + sf::Vector2i( 0, -1), 1)->onExplode();
	if (isObjectAt(position + sf::Vector2i( 1, -1), 1)) getObjectAt(position + sf::Vector2i( 1, -1), 1)->onExplode();
	if (isObjectAt(position + sf::Vector2i(-1,  0), 1)) getObjectAt(position + sf::Vector2i(-1,  0), 1)->onExplode();
	if (isObjectAt(position + sf::Vector2i( 1,  0), 1)) getObjectAt(position + sf::Vector2i( 1,  0), 1)->onExplode();
	if (isObjectAt(position + sf::Vector2i(-1,  1), 1)) getObjectAt(position + sf::Vector2i(-1,  1), 1)->onExplode();
	if (isObjectAt(position + sf::Vector2i( 0,  1), 1)) getObjectAt(position + sf::Vector2i( 0,  1), 1)->onExplode();
	if (isObjectAt(position + sf::Vector2i( 1,  1), 1)) getObjectAt(position + sf::Vector2i( 1,  1), 1)->onExplode();

	printf("Bomb exploded\n");
}

void Bomb::update(double elapsed) {
	if (active) {
		animation->update(elapsed - plantTime);
		// std::cout << "Bomb: \nelapsed time: " << elapsed << "\nplant time: " << plantTime << "\nanimation update(" << elapsed - plantTime << ")\n";
		if (elapsed - plantTime >= explosionTime) onExplode(); // explode after 3 sec
	}
}
