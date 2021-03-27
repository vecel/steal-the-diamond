#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1050), "Steal The Diamond");
    Level level(&window, "levels\\test-level.txt");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                // player.move(event.key.code)
            }
                
        }

        // check player's movement

        window.clear();

        level.draw();

        window.display();
    }

    return 0;
}