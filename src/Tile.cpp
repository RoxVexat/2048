#include "Tile.h"

#include "Game.h"
#include "Config.h"

#include <iostream>
#include <cmath> 
#include <algorithm>


std::unordered_map<int, sf::Color> Tile::colorMap = {
    {2, sf::Color(0x00, 0xff, 0x91)},
    {4, sf::Color(0x2f, 0xff, 0x00)},
    {8, sf::Color(0x88, 0xff, 0x43)},
    {16, sf::Color(0xc3, 0xff, 0x00)},
    {32, sf::Color(0xf8, 0xfc, 0x0b)},
    {64, sf::Color(0xfd, 0xc2, 0x00)},
    {128, sf::Color(0xff, 0xa2, 0x00)},
    {256, sf::Color(0xff, 0x7b, 0x00)},
    {512, sf::Color(0xfd, 0x57, 0x24)},
    {1024, sf::Color(0xff, 0x00, 0x00)},
    {2048, sf::Color(0xff, 0x00, 0xe1)},
    {4096, sf::Color(0xb3, 0x00, 0xff)},
    {8192, sf::Color(0x66, 0x00, 0xff)},
    {16384, sf::Color(0x00, 0x08, 0xff)},
    {32768, sf::Color(0x00, 0x88, 0xff)},
    {65536, sf::Color(0x00, 0xe5, 0xff)}
};


Tile::Tile(Game &game, int i, int j, int val)
    : i_(i),
      j_(j),
      newI_(i),
      newJ_(j),
      val_(val),
      merged_(false),
      game_(game),
      isPoppingUp(true),
      isNewTile(false),
      shape_(new sf::RectangleShape(sf::Vector2f(
        g_config.getTileSize(), g_config.getTileSize())))
    {   
        placeOnGrid(i, j);
        addToRenderList();
    }

Tile::~Tile()
{
    delete shape_;
}

Game& Tile::getGame() const {return game_;}
int Tile::getVal() const { return val_; }
int Tile::getI() const{ return i_; }
int Tile::getJ() const { return j_; }
int Tile::getNewI() const { return newI_; }
int Tile::getNewJ() const { return newJ_; }


float Tile::getX() const
{
    return g_config.getGridOffset() + (j_ + 1) * g_config.getGapSize() + j_* g_config.getTileSize();
}
float Tile::getY() const
{
     return g_config.getGridOffset() + (i_ + 1) * g_config.getGapSize() + i_ * g_config.getTileSize();
}
float Tile::getNewX() const
{
    return g_config.getGridOffset() + (newJ_ + 1) * g_config.getGapSize() + newJ_ * g_config.getTileSize();
}
float Tile::getNewY() const
{
    return g_config.getGridOffset() + (newI_ + 1) * g_config.getGapSize() + newI_ * g_config.getTileSize();
}

void Tile::setI(int newVal) { i_ = newVal; }
void Tile::setJ(int newVal) { j_ = newVal; }

bool Tile::isMerged() const { return merged_; }
void Tile::markAsMerged() { merged_ = true; }

void Tile::addToRenderList() { game_.getRenderList().push_back(this); }
void Tile::placeOnGrid(int i, int j)
{
    auto& grid = game_.getGrid();
    grid[i * g_config.getGridDimension() + j] = this;
}


void Tile::moveRight()
{
    auto &grid = game_.getGrid();
    const int cols = game_.getCols();
    const int curI = i_;
    int curJ = j_;
    int nextJ = curJ + 1;
    for (; nextJ < cols; curJ++, nextJ++, newJ_++) {
        if (!game_.getCell(curI, nextJ)) {
            placeOnGrid(curI, nextJ);
            game_.resetGridCell(curI, curJ);
        } else break;
    }

    if (nextJ < cols) {
        Tile *tile1 = game_.getCell(curI, curJ);
        Tile *tile2 = game_.getCell(curI, nextJ);
        if (!tile2->isNewTile && tile1->getVal() == tile2->getVal()) {
            Tile* newTile = new Tile(game_, curI, nextJ, tile1->getVal() * 2);
            newTile->isNewTile = true;
            game_.resetGridCell(curI, curJ);

            newJ_++;
            game_.score += tile1->getVal() * 2;
            tile1->markAsMerged();
            tile2->markAsMerged();
        }
    }
}

void Tile::moveLeft()
{
    auto &grid = game_.getGrid();
    const int cols = game_.getCols();
    const int curI = i_;
    int curJ = j_;
    int nextJ = curJ - 1;
    for (; nextJ >= 0; curJ--, nextJ--, newJ_--) {
        if (!game_.getCell(curI, nextJ)) {
            placeOnGrid(curI, nextJ);
            game_.resetGridCell(curI, curJ);
        } else break;
    }

    if (nextJ >= 0) {
        Tile *tile1 = game_.getCell(curI, curJ);
        Tile *tile2 = game_.getCell(curI, nextJ);
        if (!tile2->isNewTile && tile1->getVal() == tile2->getVal()) {
            Tile* newTile = new Tile(game_, curI, nextJ, tile1->getVal() * 2);
            newTile->isNewTile = true;
            game_.resetGridCell(curI, curJ);

            newJ_--;
            game_.score += tile1->getVal() * 2;
            tile1->markAsMerged();
            tile2->markAsMerged();
        }
    }
}

void Tile::moveUp()
{
    auto &grid = game_.getGrid();
    const int rows = game_.getRows();
    const int curJ = j_;
    int curI = i_;
    int nextI = curI - 1;
    for (; nextI >= 0; curI--, nextI--, newI_--) {
        if (!game_.getCell(nextI, curJ)) {
            placeOnGrid(nextI, curJ);
            game_.resetGridCell(curI, curJ);
        } else break;
    }

    if (nextI >= 0) {
        Tile *tile1 = game_.getCell(curI, curJ);
        Tile *tile2 = game_.getCell(nextI, curJ);
        if (!tile2->isNewTile && tile1->getVal() == tile2->getVal()) {
            Tile* newTile = new Tile(game_, nextI, curJ, tile1->getVal() * 2);
            newTile->isNewTile = true;
            game_.resetGridCell(curI, curJ);

            newI_--;
            game_.score += tile1->getVal() * 2;
            tile1->markAsMerged();
            tile2->markAsMerged();
        }
    }
}

void Tile::moveDown()
{
    auto &grid = game_.getGrid();
    const int rows = game_.getRows();
    int curJ = j_;
    int curI = i_;
    int nextI = curI + 1;
    for (; nextI < rows; curI++, nextI++, newI_++) {
        if (!game_.getCell(nextI, curJ)) {
            placeOnGrid(nextI, curJ);
            game_.resetGridCell(curI, curJ);
        } else break;
    }

    if (nextI < rows) {
        Tile *tile1 = game_.getCell(curI, curJ);
        Tile *tile2 = game_.getCell(nextI, curJ);
        if (!tile2->isNewTile && tile1->getVal() == tile2->getVal()) {
            Tile* newTile = new Tile(game_, nextI, curJ, tile1->getVal() * 2);
            newTile->isNewTile = true;
            game_.resetGridCell(curI, curJ);

            newI_++;
            game_.score += tile1->getVal() * 2;
            tile1->markAsMerged();
            tile2->markAsMerged();
        }
    }
}


void Tile::render()
{   

    const float tileSize = g_config.getTileSize();
    const float animTime = g_config.getAnimTime();
    const float fontSize = g_config.getFontSize();

    sf::Text text(game_.font);

    text.setString(std::to_string(val_));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize((fontSize - static_cast<int>(std::log10(val_)) * 12.0f * tileSize / 120.0f));

    if (isPoppingUp)
        text.setCharacterSize(text.getCharacterSize() * game_.animTimePassed / animTime);

    const sf::FloatRect textBounds = text.getLocalBounds();

    text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f
    });

    float x = getX() + (getNewX() - getX()) * game_.animTimePassed / animTime;
    float y = getY() + (getNewY() - getY()) * game_.animTimePassed / animTime;
    
    if (isPoppingUp) {
        const float popUpSize = tileSize *  game_.animTimePassed / animTime;
        float popUpX = x + (tileSize - popUpSize) / 2;
        float popUpY = y + (tileSize - popUpSize) / 2;
        shape_->setSize({popUpSize, popUpSize});
        shape_->setPosition({popUpX, popUpY});
    } else {
        shape_->setSize({tileSize, tileSize});
        shape_->setPosition({x, y});
    }

    sf::Color tileColor;
    auto it = colorMap.find(val_);
    if (it != colorMap.end()) 
        tileColor = it->second;
    else 
        tileColor = sf::Color::White;

    shape_->setFillColor(tileColor);

    text.setPosition({
        x + tileSize / 2,
        y + tileSize / 2
    });

    game_.getSceneBuffer().draw(*shape_);
    game_.getSceneBuffer().draw(text);
}

