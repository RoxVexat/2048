#pragma once

#include <vector>

class Tile;
namespace sf {
    class Font;
    class RenderWindow;
}

class Game
{
    public:
        static sf::Font font;

        Game();
        
        int getCols() const;
        int getRows() const;
        Tile* getCell(int i, int j) const;
        const std::vector<Tile*>& getGrid() const;
        const std::vector<Tile*>& getRenderList() const;

        std::vector<Tile*>& getGrid();
        std::vector<Tile*>& getRenderList();

        void isMoveLeftAvailable();
        void isMoveRightAvailable();
        void isMoveUpAvailable();
        void isMoveDownAvailable();
        
        void addTileToRenderList(Tile* tile);
        void removeTileFromRenderList(Tile * tile);
        void placeTileOnGrid(Tile* tile, int i, int j);
        void resetGridCell(int i, int j);
        void generateRandomTile();

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        
        void draw(sf::RenderWindow& window);

    private:
        int cols_;
        int rows_;
        std::vector<Tile*> grid_;
        std::vector<Tile*> renderList_;
};