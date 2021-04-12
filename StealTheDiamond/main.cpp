#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1050), "Steal The Diamond");
    Level level(&window, "levels\\test-level-2.txt");

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

        // std::cout << "Objects: " << level.objects.size() << '\n';

        window.clear();

        level.updateLevel();

        level.draw();

        window.display();
    }

    return 0;
}
