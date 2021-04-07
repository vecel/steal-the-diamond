#pragma once
#include <SFML/Graphics.hpp>

class Exit : public sf::RectangleShape
{
public:
	Exit(sf::Vector2i pos, std::string txtPath);
	~Exit();

	sf::Vector2i position;

private:
	sf::Texture texture;
};

