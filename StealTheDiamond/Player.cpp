#include "Player.h"
#include "Level.h"
#include <iostream> // just for debugging
#include "Wall.h"

Player::Player(Level* level, sf::Vector2i pos) : Object(level, pos) {
	
	// create and load the texture
	if (!texture.loadFromFile("textures\\player.png")) {
		printf("Cannot load the texture\n");
	}
	sprite.setTexture(texture);

	flags = MOVABLE | DROWNING;
}

Player::~Player() {
	printf("Player destructor\n");
}

void Player::update() {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) move(sf::Vector2i(-1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) move(sf::Vector2i(1, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) move(sf::Vector2i(0, -1));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) move(sf::Vector2i(0, 1));

}

bool Player::move(sf::Vector2i dir) { 
	return Object::move(dir);
}

bool Player::onSinking() {
	printf("player drowned\n");
	level->tileMap->setObjectAt(position, nullptr);
	level->activePlayer = nullptr;
	//delete this; // usun jeszcze z level.objects
	level->addObjectToRemove(this);
	// usuwa obiekt, ale zostaje wskaznik na pusta pamiec - niebezbieczne!!!

	return false;
}

