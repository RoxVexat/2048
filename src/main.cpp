#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Tile.hpp>
#include <Game.hpp>
#include <iostream>


void printGrid(Game &game) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (game.hasTile(i, j)) std::cout << "1 ";
            else std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

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
                game.printTileCoords();
                // printGrid(game);
                // std::cout << tile1.getI() << ", " << tile1.getJ();
            }
        }
        window.clear(sf::Color::Black);
        game.draw(window);
        window.display();
    }
}
