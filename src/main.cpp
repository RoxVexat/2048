#include "Tile.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "My window");
    
    Game game;

    while (window.isOpen())
    {   
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const sf::Event::KeyPressed *keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                switch (keyPressed->scancode)
                {
                    case sf::Keyboard::Scancode::R:
                        game.reset();
                        break;
                    case sf::Keyboard::Scancode::W:
                    case sf::Keyboard::Scancode::Up:
                        if (game.isMoveUpAvailable()) {
                            game.moveUp();
                            game.generateRandomTile();
                        }
                        break;
                    case sf::Keyboard::Scancode::S:
                    case sf::Keyboard::Scancode::Down:
                        if (game.isMoveDownAvailable()) {
                            game.moveDown();
                            game.generateRandomTile();
                        }
                        break;
                    case sf::Keyboard::Scancode::A:
                    case sf::Keyboard::Scancode::Left:
                        if (game.isMoveLeftAvailable()) {
                            game.moveLeft();
                            game.generateRandomTile();
                        }   
                        break;
                    case sf::Keyboard::Scancode::D:
                    case sf::Keyboard::Scancode::Right:
                        if (game.isMoveRightAvailable()) {
                            game.moveRight();
                            game.generateRandomTile();
                        }
                        break;
                }

            }
        }
        window.clear(sf::Color::Black);
        game.draw(window);
        window.display();
    }
}
