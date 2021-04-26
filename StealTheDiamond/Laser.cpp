#include "Laser.h"

int Laser::defaultId = 43;

Laser::Laser(Level* level, sf::Vector2i pos, int id, int layer) : Object(level, pos, defaultId, layer) {

	flags = DESTROYABLE;
	setFacing(id); // rotate laser only after setting its texture (in object constructor)
	
}

Laser::~Laser(){}

void Laser::onRender() {
	// change origin and set rotation
	float o_x = sprite.getTextureRect().width / 2;
	float o_y = sprite.getTextureRect().height / 2;
	sprite.setOrigin(o_x, o_y);
	sprite.move(o_x, o_y);
	sprite.setRotation(90 * (int)(facing));
	
	// set laser beam texture

}

void Laser::update(double elapsed) {

}

void Laser::renderLaserBeam() {

}

void Laser::setFacing(int laserId) {
	facing = (Facing)(laserId - defaultId);

	switch (facing) {
	case Facing::UP: facingVector = sf::Vector2i(0, -1); break;
	case Facing::RIGHT: facingVector = sf::Vector2i(1, 0); break;
	case Facing::DOWN: facingVector = sf::Vector2i(0, 1); break;
	case Facing::LEFT: facingVector = sf::Vector2i(-1, 0); break;
	}

	// TODO set laser beam texture 0,2 vertically / 1,3 horizontally
}


