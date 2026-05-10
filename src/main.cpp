#include "Tile.hpp"
#include "Game.hpp"
#include "Config.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "2048");
    
    Game game;
    sf::Clock clock;

    while (window.isOpen())
    {   
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const sf::Event::KeyPressed *keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                game.endMoveAnim();

                game.handleKeyPress(keyPressed);

                game.startMoveAnim();

            }
        }

        game.update(dt);

        window.clear(sf::Color::Black);
        game.draw(window);
        window.display();
    }
}


