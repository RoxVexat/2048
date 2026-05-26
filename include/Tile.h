#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class Game;

class Tile
{
    public:

        static std::unordered_map<int, sf::Color> colorMap;

        Tile(Game &game, int i, int j, int val);
        ~Tile();

        bool isPoppingUp;
        bool isNewTile;

        Game& getGame() const;
        int getVal() const;
        int getI() const;
        int getJ() const;
        int getNewI() const;
        int getNewJ() const;
        float getX() const;
        float getY() const;
        float getNewX() const;
        float getNewY() const;

        void setI(int newVal);
        void setJ(int newVal);

        bool isMerged() const;
        void markAsMerged();
        void addToRenderList();
        void placeOnGrid(int i, int j);

        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();

        void render();

    private:

        Game &game_;
        sf::RectangleShape* shape_;

        int i_;
        int j_;

        int newI_;
        int newJ_;
        bool merged_;
        int val_;
};