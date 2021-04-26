#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "Player.h"

void showInfo(Level& level);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 1050), "Steal The Diamond");
    window.setFramerateLimit(60);

    Level level(&window, "levels\\level-4.txt");
    level.onRender();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    if (level.activePlayer != nullptr) {
                        switch (event.key.code) {
                        case sf::Keyboard::Up: level.activePlayer->move(sf::Vector2i(0, -1)); break;
                        case sf::Keyboard::Down: level.activePlayer->move(sf::Vector2i(0, 1)); break;
                        case sf::Keyboard::Right: level.activePlayer->move(sf::Vector2i(1, 0)); break;
                        case sf::Keyboard::Left: level.activePlayer->move(sf::Vector2i(-1, 0)); break;
                        default: break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Tab) level.switchActivePlayer();
            }
                
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) showInfo(level);

        window.clear();

        level.updateLevel();

        level.draw();

        window.display();
    }

    return 0;
}

void showInfo(Level& level) {
    std::cout << "\nObjects: " << level.objects.size() << '\n';
    if (level.activePlayer == nullptr) return;

    std::cout << "Keys: " << level.activePlayer->keys.size() << "\nKey ids : ";
    for (int i : level.activePlayer->keys) std::cout << i << " ";
    std::cout << '\n';
    std::cout << "Bombs: " << level.activePlayer->bombs << '\n';
    std::cout << "Elapsed time: " << level.activePlayer->getElapsedTime() << '\n';
    std::cout << "Active player: " << level.activePlayer << '\n';
    std::cout << "PlayerIndex: " << level.playerIndex << '\n';
}
