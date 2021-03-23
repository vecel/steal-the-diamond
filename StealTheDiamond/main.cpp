#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileMap.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1360, 768), "Steal The Diamond");

    TileMap* tileMap = new TileMap(&window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                //delete tileMap;
            }
                
        }

        window.clear();

        tileMap->draw();
        tileMap->clear();

        window.display();
    }

    return 0;
}