#include "Game.hpp"

#include <algorithm>
#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

#include "Tile.hpp"

sf::Font Game::font("arial.ttf");

Game::Game()
    : rows_(4), cols_(4), grid_(rows_ * cols_)
{
    generateRandomTile();
    generateRandomTile();
}

void Game::draw(sf::RenderWindow &window)
{
    for (auto tile : renderList_)
    {
        tile->draw(window);
    }
}

int Game::getRows() const { return rows_; }
int Game::getCols() const { return cols_; }
const std::vector<Tile *> &Game::getGrid() const { return grid_; }
const std::vector<Tile *> &Game::getRenderList() const { return renderList_; }
Tile *Game::getCell(int i, int j) const
{
     return grid_[i * cols_ + j];
}

std::vector<Tile *> &Game::getGrid() { return grid_; }
std::vector<Tile *> &Game::getRenderList() { return renderList_; }

void Game::addTileToRenderList(Tile *tile)
{
    renderList_.push_back(tile);
}

void Game::removeTileFromRenderList(Tile *tile)
{
    renderList_.erase(std::remove(renderList_.begin(), renderList_.end(), tile), renderList_.end());
}

void Game::placeTileOnGrid(Tile *tile, int i, int j)
{
    grid_[i * cols_ + j] = tile;
}

void Game::resetGridCell(int i, int j)
{
    grid_[i * cols_ + j] = nullptr;
}

void Game::generateRandomTile() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rowDist(0, rows_ - 1);
    std::uniform_int_distribution<> colDist(0, cols_ - 1);
    std::uniform_int_distribution<> shiftDist(0, 1);

    int randI = rowDist(gen);
    int randJ = colDist(gen);
    
    while (getCell(randI, randJ)) {
        randI = rowDist(gen);
        randJ = colDist(gen);
    } 
    
    int shift = shiftDist(gen);
    Tile* newTile = new Tile(*this, randI, randJ, 2 << shift);
}

void Game::moveLeft()
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < rows_; j++)
        {
            auto tile = getCell(i, j);
            if (tile)
                tile->moveLeft();
        }
    }
}

void Game::moveRight()
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = cols_ - 1; j >= 0; j--)
        {
            auto tile = getCell(i, j);
            if (tile)
                tile->moveRight();
        }
    }
}

void Game::moveUp()
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            auto tile = getCell(i, j);
            if (tile)
                tile->moveUp();
        }
    }
}

void Game::moveDown()
{
    for (int i = rows_ - 1; i >= 0; i--)
    {
        for (int j = 0; j < cols_; j++)
        {
            auto tile = getCell(i, j);
            if (tile)
                tile->moveDown();
        }
    }
}