#include "Tile.hpp"

#include <iostream>
#include <cmath> 

#include <SFML/Graphics.hpp>

#include "Game.hpp"


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
};

Tile::Tile(Game &game, int i, int j, int val)
    : i(i),
      j(j),
      newI(i),
      newJ(j),
      val(val),
      game(game),
      merged(false),
      isPoppingUp(true),
      shape(new sf::RectangleShape(sf::Vector2f(size, size)))
    {   
        game.placeTileOnGrid(this, i, j);
        game.addTileToRenderList(this);
        game.numTiles++;
    }

Tile::~Tile() {
    delete shape;
    game.numTiles--;
}

float Tile::getX() const
{
    return (j + 1) * 40 + j * size;
}
float Tile::getY() const
{
    return (i + 1) * 40 + i * size;
}
float Tile::getNewX() const
{
    return (newJ + 1) * 40 + newJ * size;
}
float Tile::getNewY() const
{
    return (newI + 1) * 40 + newI * size;
}
bool Tile::isMerged() const { return merged; }

void Tile::markAsMerged() { merged = true; }

int Tile::getI() const{ return i; }
int Tile::getJ() const { return j; }
int Tile::getNewI() const { return newI; }
int Tile::getNewJ() const { return newJ; }
int Tile::getVal() const { return val; }

void Tile::setI(int newVal) { i = newVal; }
void Tile::setJ(int newVal) { j = newVal; }

void Tile::moveRight() {
    auto &grid = game.getGrid();
    int cols = game.getCols();
    const int curI = getI();
    int curJ = getJ();
    int nextJ = curJ + 1;
    for (; nextJ < cols; curJ++, nextJ++, newJ++) {
        if (!game.getCell(curI, nextJ)) {
            game.placeTileOnGrid(this, curI, nextJ);
            game.resetGridCell(curI, curJ);
        } else break;
    }

    if (nextJ < cols) {
        Tile *tile1 = game.getCell(curI, curJ);
        Tile *tile2 = game.getCell(curI, nextJ);
        if (tile1->val == tile2->val) {
            Tile* newTile = new Tile(game, curI, nextJ, tile1->val * 2);
            game.resetGridCell(curI, curJ);

            newJ++;
            tile1->markAsMerged();
            tile2->markAsMerged();
            
        }
    }
};

void Tile::moveLeft() {
    auto &grid = game.getGrid();
    int cols = game.getCols();
    const int curI = getI();
    int curJ = getJ();
    int nextJ = curJ - 1;
    for (; nextJ >= 0; curJ--, nextJ--, newJ--) {
        if (!game.getCell(curI, nextJ)) {
            game.placeTileOnGrid(this, curI, nextJ);
            game.resetGridCell(curI, curJ);
        } else break;
    }

    if (nextJ >= 0) {
        Tile *tile1 = game.getCell(curI, curJ);
        Tile *tile2 = game.getCell(curI, nextJ);
        if (tile1->val == tile2->val) {
            Tile* newTile = new Tile(game, curI, nextJ, tile1->val * 2);
            game.resetGridCell(curI, curJ);

            newJ--;
            tile1->markAsMerged();
            tile2->markAsMerged();
        }
    }
};

void Tile::moveUp() {
    auto &grid = game.getGrid();
    int rows = game.getRows();
    const int curJ = getJ();
    int curI = getI();
    int nextI = curI - 1;
    for (; nextI >= 0; curI--, nextI--, newI--) {
        if (!game.getCell(nextI, curJ)) {
            game.placeTileOnGrid(this, nextI, curJ);
            game.resetGridCell(curI, curJ);
        } else break;
    }

    if (nextI >= 0) {
        Tile *tile1 = game.getCell(curI, curJ);
        Tile *tile2 = game.getCell(nextI, curJ);
        if (tile1->val == tile2->val) {
            Tile* newTile = new Tile(game, nextI, curJ, tile1->val * 2);
            game.resetGridCell(curI, curJ);

            newI--;
            tile1->markAsMerged();
            tile2->markAsMerged();
        }
    }
};

void Tile::moveDown(){
    auto &grid = game.getGrid();
    int rows = game.getRows();
    const int curJ = getJ();
    int curI = getI();
    int nextI = curI + 1;
    for (; nextI < rows; curI++, nextI++, newI++) {
        if (!game.getCell(nextI, curJ)) {
            game.placeTileOnGrid(this, nextI, curJ);
            game.resetGridCell(curI, curJ);
        } else break;
    }

    if (nextI < rows) {
        Tile *tile1 = game.getCell(curI, curJ);
        Tile *tile2 = game.getCell(nextI, curJ);
        if (tile1->val == tile2->val) {
            Tile* newTile = new Tile(game, nextI, curJ, tile1->val * 2);
            game.resetGridCell(curI, curJ);

            newI++;
            tile1->markAsMerged();
            tile2->markAsMerged();
        }
    }
}


void Tile::draw(sf::RenderWindow& window)
{   
    sf::Text text(game.font);
    
    text.setString(std::to_string(val));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize((100 - static_cast<int>(std::log10(val)) * 12));
    
    if (isPoppingUp)
        text.setCharacterSize(text.getCharacterSize() * game.animTimePassed / ANIM_TIME);

    const sf::FloatRect textBounds = text.getLocalBounds();

    text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f
    });

    float x = getX() + (getNewX() - getX()) * game.animTimePassed / ANIM_TIME;
    float y = getY() + (getNewY() - getY()) * game.animTimePassed / ANIM_TIME;
    
    if (isPoppingUp) {
        const float popUpSize = size *  game.animTimePassed / ANIM_TIME;
        float popUpX = x + (size - popUpSize) / 2;
        float popUpY = y + (size - popUpSize) / 2;
        shape->setSize({popUpSize, popUpSize});
        shape->setPosition({popUpX, popUpY});
    } else {
        shape->setSize({size, size});
        shape->setPosition({x, y});
    }

    sf::Color tileColor;
    auto it = colorMap.find(val);
    if (it != colorMap.end()) 
        tileColor = it->second;
    else 
        tileColor = sf::Color::White;

    shape->setFillColor(tileColor);

    text.setPosition({
        x + size / 2,
        y + size / 2
    });

    window.draw(*shape);
    window.draw(text);
}

