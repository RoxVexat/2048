#include "Game.hpp"

#include "Tile.hpp"
#include "Config.hpp"

#include <algorithm>
#include <iostream>
#include <random>


sf::Font Game::font("arial.ttf");

Game::Game()
    : rows_(g_config.getGridDimension()),
      cols_(g_config.getGridDimension()),
      grid_(rows_ * cols_),
      animTimePassed(g_config.getAnimTime()),
      areTilesMoving(false),
      numTiles(0)
{
    generateRandomTile();
    generateRandomTile();
}

Game::~Game()
{
    cleanUp();
}

int Game::getRows() const { return rows_; }
int Game::getCols() const { return cols_; }
const std::vector<Tile *> &Game::getGrid() const { return grid_; }
const std::vector<Tile *> &Game::getRenderList() const { return renderList_; }
Tile *Game::getCell(int i, int j) const
{
    return grid_[i * cols_ + j];
}

std::vector<Tile *>& Game::getGrid() { return grid_; }
std::vector<Tile *>& Game::getRenderList() { return renderList_; }

bool Game::gameOver() const
{
    return !(
        isMoveLeftAvailable() ||
        isMoveRightAvailable() ||
        isMoveUpAvailable() ||
        isMoveDownAvailable());
}

bool Game::isMoveLeftAvailable() const
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 1; j < cols_; j++)
        {
            auto curTile = getCell(i, j);
            if (curTile)
            {
                auto leftTile = getCell(i, j - 1);
                if (!leftTile || curTile->getVal() == leftTile->getVal())
                    return true;
            }
        }
    }
    return false;
}

bool Game::isMoveRightAvailable() const
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_ - 1; j++)
        {
            auto curTile = getCell(i, j);
            if (curTile)
            {
                auto rightTile = getCell(i, j + 1);
                if (!rightTile || curTile->getVal() == rightTile->getVal())
                    return true;
            }
        }
    }
    return false;
}

bool Game::isMoveUpAvailable() const
{
    for (int i = 1; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            auto curTile = getCell(i, j);
            if (curTile)
            {
                auto topTile = getCell(i - 1, j);
                if (!topTile || curTile->getVal() == topTile->getVal())
                    return true;
            }
        }
    }
    return false;
}

bool Game::isMoveDownAvailable() const
{
    for (int i = 0; i < rows_ - 1; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            auto curTile = getCell(i, j);
            if (curTile)
            {
                auto bottomTile = getCell(i + 1, j);
                if (!bottomTile || curTile->getVal() == bottomTile->getVal())
                    return true;
            }
        }
    }
    return false;
}

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

void Game::generateRandomTile()
{

    if (gameOver() && numTiles > 2)
        return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rowDist(0, rows_ - 1);
    std::uniform_int_distribution<> colDist(0, cols_ - 1);
    std::uniform_int_distribution<> powerDist(1, 2);

    int randI = rowDist(gen);
    int randJ = colDist(gen);

    while (getCell(randI, randJ))
    {
        randI = rowDist(gen);
        randJ = colDist(gen);
    }

    int power = powerDist(gen);
    Tile *newTile = new Tile(*this, randI, randJ, 1 << power);
}

void Game::cleanMerged()
{
    for (auto &tile : renderList_)
    {
        if (tile && tile->isMerged())
        {
            delete tile;
            tile = nullptr;
        }
    }

    renderList_.erase(std::remove(renderList_.begin(), renderList_.end(), nullptr), renderList_.end());
}

void Game::removeNewTileFlag() {
    for (auto &tile : renderList_)
    {
        tile->isNewTile = false;
    }
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
    removeNewTileFlag();
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
    removeNewTileFlag();
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
    removeNewTileFlag();
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
    removeNewTileFlag();
}

void Game::handleKeyPress(const sf::Event::KeyPressed& keyPressed, sf::RenderWindow& window) {
    switch (keyPressed.scancode)
    {
        case sf::Keyboard::Scancode::R:
            reset();
            break;

        case sf::Keyboard::Scancode::Escape:
            window.close();

        
        case sf::Keyboard::Scancode::Equal:
        case sf::Keyboard::Scancode::NumpadPlus:
            g_config.setGridSize(g_config.getGridSize() + 50);
            break;

        case sf::Keyboard::Scancode::Hyphen:
        case sf::Keyboard::Scancode::NumpadMinus:
            g_config.setGridSize(g_config.getGridSize() - 50);
            break;
        
        case sf::Keyboard::Scancode::Num4:
            g_config.setGridDimension(4);
            reset();
            break;

        case sf::Keyboard::Scancode::Num5:
            g_config.setGridDimension(5);
            reset();
            break;

        case sf::Keyboard::Scancode::Num6:
            g_config.setGridDimension(6);
            reset();
            break;

        case sf::Keyboard::Scancode::Num7:
            g_config.setGridDimension(7);
            reset();
            break;
            
        case sf::Keyboard::Scancode::Num8:
            g_config.setGridDimension(8);
            reset();
            break;
            

        case sf::Keyboard::Scancode::W:
        case sf::Keyboard::Scancode::Up:
            if (isMoveUpAvailable()) {
                moveUp();
                generateRandomTile();
            }
            break;
        case sf::Keyboard::Scancode::S:
        case sf::Keyboard::Scancode::Down:
            if (isMoveDownAvailable()) {
                moveDown();
                generateRandomTile();
            }
            break;
        case sf::Keyboard::Scancode::A:
        case sf::Keyboard::Scancode::Left:
            if (isMoveLeftAvailable()) {
                moveLeft();
                generateRandomTile();
            }   
            break;
        case sf::Keyboard::Scancode::D:
        case sf::Keyboard::Scancode::Right:
            if (isMoveRightAvailable()) {
                moveRight();
                generateRandomTile();
            }
            break;
    }

    std::cout << numTiles << "\n";
}


void Game::cleanUp()
{
    for (auto tile : renderList_)
        delete tile;

    renderList_.clear();

    for (auto &ptr : grid_)
    {
        ptr = nullptr;
    }
}

void Game::reset()
{

    cleanUp();
    numTiles = 0;   

    rows_ = g_config.getGridDimension();
    cols_ = g_config.getGridDimension();
    
    grid_.resize(rows_ * cols_);

    generateRandomTile();
    generateRandomTile();
}

void Game::update(float deltaTime)
{
    if (areTilesMoving)
    {
        animTimePassed = std::min(g_config.getAnimTime(), animTimePassed + deltaTime);
        if (animTimePassed == g_config.getAnimTime())
        {
            areTilesMoving = false;
        }
    }
}
void Game::startMoveAnim()
{
    areTilesMoving = true;
    animTimePassed = 0;
}

void Game::endMoveAnim()
{
    for (auto tile : renderList_)
    {
        tile->setI(tile->getNewI());
        tile->setJ(tile->getNewJ());
        tile->isPoppingUp = false;
    }

    areTilesMoving = false;
    cleanMerged();
}

void Game::draw(sf::RenderWindow &window)
{
    drawGridBackground(window);
    for (auto tile : renderList_)
    {
        tile->draw(window);
    }
}

void Game::drawGridBackground(sf::RenderWindow &window)
{   
    const float tileSize = g_config.getTileSize();
    const float gridSize = g_config.getGridSize();
    const float gapSize = g_config.getGapSize();
    const float gridLineWidth = g_config.getGridLineWidth();
    const float gridOffset = g_config.getGridOffset();

    const float bgSize = gridSize;
    const float lineOffset = (gapSize - gridLineWidth) / 2;  

    sf::RectangleShape bg({bgSize - lineOffset*2, bgSize-lineOffset*2});
    bg.setPosition({gridOffset+lineOffset, gridOffset+lineOffset});

    bg.setFillColor(sf::Color(42, 42, 42)); 
    window.draw(bg);

    for (int i = 0; i <= rows_; i++)
    {   
        
        float lineCoord1 = gridOffset + lineOffset;
        float lineCoord2 = gridOffset + tileSize *i + gapSize*i + lineOffset;
        sf::RectangleShape vLine({gridLineWidth, bgSize - 2*lineOffset});
        sf::RectangleShape hLine({bgSize - 2*lineOffset, gridLineWidth});

        vLine.setPosition({lineCoord2, lineCoord1});
        hLine.setPosition({lineCoord1, lineCoord2});

        sf::Color lineColor(20, 20, 20);
        vLine.setFillColor(lineColor);
        hLine.setFillColor(lineColor);

        window.draw(vLine);
        window.draw(hLine);
    }
}
