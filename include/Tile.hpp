#pragma once
#include <SFML/Graphics.hpp>

class Game;
enum class Direction;

class Tile {
    private:
        static inline int size = 150;
        sf::RectangleShape shape;
        int i;
        int j;
    public:
        Tile(Game &game, int i, int j);
        float getX() const;
        float getY() const;
        void draw(sf::RenderWindow &window);
        int getI() const;
        int getJ() const;
        void setGridPos(int i, int j);
        void move(Game &game, Direction direction);
        void moveRight(Game &game);
        void moveLeft(Game &game);
        void moveUp(Game &game);
        void moveDown(Game &game);

};