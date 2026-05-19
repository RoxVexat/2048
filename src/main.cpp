#include "Game.h"
#include "Config.h"
#include "Data.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(
        {g_config.getWindowSize(), g_config.getWindowSize()}
    ), "2048");
    
    Game game;
    sf::Clock clock;
    Data::loadHighScores();
    
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

                game.handleKeyPress(*keyPressed, window);

                game.startMoveAnim();

            }
        }

        game.update(dt);

        window.clear(sf::Color::Black);
        game.draw(window);
        window.display();
    }
}