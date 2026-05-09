#pragma once

#include <vector>
#include <unordered_map>

class Tile;

namespace sf {
    class Font;
    class RenderWindow;
}

class Game
{
    public:
        static sf::Font font;

        int numTiles;

        Game();
        ~Game();
        
        void reset();
        
        int getCols() const;
        int getRows() const;
        Tile* getCell(int i, int j) const;
        const std::vector<Tile*>& getGrid() const;
        const std::vector<Tile*>& getRenderList() const;

        std::vector<Tile*>& getGrid();
        std::vector<Tile*>& getRenderList();

        bool gameOver() const;
        bool isMoveLeftAvailable() const;
        bool isMoveRightAvailable() const;
        bool isMoveUpAvailable() const;
        bool isMoveDownAvailable() const;

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
        void cleanUp();
        int cols_;
        int rows_;
        std::vector<Tile*> grid_;
        std::vector<Tile*> renderList_;
};