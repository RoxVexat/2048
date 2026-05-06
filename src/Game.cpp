#include <Game.hpp>
#include <random>

Game::Game()
        : rows_(4), cols_(4), grid(rows_ * cols_)
    {
        // std::random_device rd;
        // std::mt19937 gen(rd());
        // std::uniform_int_distribution<> rowDist(0, rows_ - 1);
        // std::uniform_int_distribution<> colDist(0, cols_ - 1);

        // int row1 = rowDist(gen);
        // int col1 = colDist(gen);
        // grid[row1 * cols_ + col1] = Tile(row1, col1);

        // int row2, col2;
        // do
        // {
        //     row2 = rowDist(gen);
        //     col2 = colDist(gen);
        // } while (row2 == row1 && col2 == col1);

        // grid[row2 * cols_ + col2] = Tile(row2, col2);
    }

void Game::draw(sf::RenderWindow &window)
    {
        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                auto &tile = grid[i * cols_ + j];
                if (tile.has_value())
                {
                    tile->draw(window);
                }
            }
        }
    }

int Game::getRows() const {return rows_;}
int Game::getCols() const {return cols_;}
std::vector<std::optional<Tile>>& Game::getGrid() {return grid;}
const std::vector<std::optional<Tile>>&  Game::getGrid() const {return grid;}

bool Game::isValidCell(int i, int j) const {
    return (i >= 0 && i < getRows()) &&
           (j >= 0 && j < getCols());

}
bool Game::hasTile(int i, int j) const {
    return isValidCell(i, j) && getGrid()[i * getCols() + j].has_value();
}

void Game::setTile(const Tile& tile, int i, int j) {
    grid[i * getCols() + j] = tile;
}

void Game::resetCell(int i, int j) {
    grid[i * getCols() + j].reset();
}