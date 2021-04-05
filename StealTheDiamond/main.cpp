#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "Player.h"

bool func() { return 1; }

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1050), "Steal The Diamond");
    Level level(&window, "levels\\test-level.txt");

    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
                
        }

        // check player's movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) if(level.activePlayer->move(sf::Vector2i(-1, 0)));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) if(level.activePlayer->move(sf::Vector2i(1, 0)));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) if(level.activePlayer->move(sf::Vector2i(0, -1)));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) level.activePlayer->move(sf::Vector2i(0, 1));

        func();

        window.clear();

        level.draw();

        window.display();
    }

    return 0;
}