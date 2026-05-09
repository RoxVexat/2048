#pragma once

class Game;
namespace sf {
    class RectangleShape;
    class RenderWindow;
}

class Tile {
    
    public:
        Tile(Game &game, int i, int j, int val);
        ~Tile();

        float getX() const;
        float getY() const;

        int getI() const;
        int getJ() const;

        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();

        void draw(sf::RenderWindow &window);

    private:
        static inline int size = 150;
        sf::RectangleShape* shape;
        Game &game;
        int i;
        int j;
        int val;
};