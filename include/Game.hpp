#pragma once
#include <array>
#include <optional>
#include <vector>
#include "Tile.hpp"
enum class Direction { Up, Down, Left, Right };

class Game
{
    private:
        int cols_;
        int rows_;
        std::vector<std::optional<Tile>> grid;
    public:
        Game();
        
        std::vector<std::optional<Tile>>& getGrid();
        const std::vector<std::optional<Tile>>& getGrid() const;
        int getCols() const;
        int getRows() const;
        
        bool hasTile(int i, int j) const;
        void setTile(const Tile& tile, int i, int j);

        bool isValidCell(int i, int j) const;
        void resetCell(int i, int j);
        

        void draw(sf::RenderWindow& window);
    };