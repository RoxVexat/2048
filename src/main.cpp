#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Tile.hpp>
#include <Game.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "My window");
    
    Game game;
    Tile tile1(game, 0, 0);
    Tile tile2(game, 0, 3);


    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const sf::Event::KeyPressed *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode)
                {
                    case sf::Keyboard::Scancode::W:
                        tile1.moveUp(game);
                        break;
                    case sf::Keyboard::Scancode::S:
                        tile1.moveDown(game);
                        break;
                    case sf::Keyboard::Scancode::A:
                        tile1.moveLeft(game);
                        break;
                    case sf::Keyboard::Scancode::D:
                        tile1.moveRight(game);
                        break;
                }
                std::cout << tile1.getI() << ", " << tile1.getJ()  << "\n";
            }
        }

        window.clear(sf::Color::Black);
        tile1.draw(window);
        tile2.draw(window);
        window.display();
    }
}
