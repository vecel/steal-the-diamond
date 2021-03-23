#include "Wall.h"

Wall::Wall(int x, int y) {
	rect.setSize(sf::Vector2f(32.0f, 32.0f));
	rect.setPosition(sf::Vector2f(10.0f + 32 * x, 10.0f + 32 * y));

	if((x + y) % 2 == 0) rect.setFillColor(sf::Color::Blue);
	else rect.setFillColor(sf::Color::White);
}
