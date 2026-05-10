#include "Tile.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "Config.hpp"

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

                switch (keyPressed->scancode)
                {
                    case sf::Keyboard::Scancode::R:
                        game.reset();
                        break;

                    case sf::Keyboard::Scancode::Num4:
                        g_config.setGridDimension(4);
                        game.reset();
                        break;

                    case sf::Keyboard::Scancode::Num5:
                        g_config.setGridDimension(5);
                        game.reset();
                        break;

                    case sf::Keyboard::Scancode::Num6:
                        g_config.setGridDimension(6);
                        game.reset();
                        break;

                    case sf::Keyboard::Scancode::Num7:
                        g_config.setGridDimension(7);
                        game.reset();
                        break;
                        
                    case sf::Keyboard::Scancode::Num8:
                        g_config.setGridDimension(8);
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

                game.startMoveAnim();

            }
        }

        game.update(dt);

        window.clear(sf::Color::Black);
        game.draw(window);
        window.display();
    }
}
