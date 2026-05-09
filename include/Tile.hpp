#pragma once

#include <unordered_map>

class Game;
namespace sf {
    class RectangleShape;
    class RenderWindow;
    class Color;
}

class Tile {
    
    public:
        
        static std::unordered_map<int, sf::Color> colorMap;

        Tile(Game &game, int i, int j, int val);
        ~Tile();

        float getX() const;
        float getY() const;
        float getNewX() const;
        float getNewY() const;

        int getI() const;
        int getJ() const;
        int getNewI() const;
        int getNewJ() const;

        void setI(int newVal);
        void setJ(int newVal);

        int getVal() const;

        bool isMerged() const;
        void markAsMerged();

        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();

        void update(float deltaTime);

        void draw(sf::RenderWindow &window);

    private:
        static inline int size = 150;
        sf::RectangleShape* shape;
        Game &game;

        int i;
        int j;

        int newI;
        int newJ;
        bool merged;
        int val;
};