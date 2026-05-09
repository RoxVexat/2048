#include <Tile.hpp>
#include <Game.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
                    case sf::Keyboard::Scancode::W:
                        game.moveUp();
                        game.generateRandomTile();
                        break;
                    case sf::Keyboard::Scancode::S:
                        game.moveDown();
                        game.generateRandomTile();
                        break;
                    case sf::Keyboard::Scancode::A:
                        game.moveLeft();
                        game.generateRandomTile();
                        break;
                    case sf::Keyboard::Scancode::D:
                        game.moveRight();
                        game.generateRandomTile();
                        break;
                }
            }
        }
        window.clear(sf::Color::Black);
        game.draw(window);
        window.display();
    }
}
