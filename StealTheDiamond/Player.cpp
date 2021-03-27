#include "Player.h"

Player::Player(sf::Vector2i pos) : Object(pos) {
	
	// create and load the texture
	if (!texture.loadFromFile("textures\\player-test.png")) {
		printf("Cannot load the texture\n");
	}
	sprite.setTexture(texture);

	sprite.setPosition(sf::Vector2f(10.0f + size * position.x, 10.0f + size * position.y));
}

/*void Player::move(sf::Keyboard::Key k) {
	float moveX = 0.0f, moveY = 0.0f;
	switch (k) {
	case sf::Keyboard::Left: moveX = -32.0f; break;
	case sf::Keyboard::Right: moveX = 32.0f; break;
	case sf::Keyboard::Up: moveY = -32.0f; break;
	case sf::Keyboard::Down: moveY = 32.0f; break;
	}
	sprite.move(moveX, moveY);
	// change pointers in tileMap's array
}*/
