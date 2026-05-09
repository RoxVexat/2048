#include "Tile.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Game.hpp"

Tile::Tile(Game &game, int i, int j, int val)
    : i(i),
      j(j),
      val(val),
      game(game),
      shape(new sf::RectangleShape(sf::Vector2f(size, size)))
    {   
        game.placeTileOnGrid(this, i, j);
        game.addTileToRenderList(this);
    }

Tile::~Tile() {
    game.removeTileFromRenderList(this);
}

float Tile::getX() const
{
    return (j + 1) * 40 + j * size;
}
float Tile::getY() const
{
    return (i + 1) * 40 + i * size;
}

int Tile::getI() const{ return i; }
int Tile::getJ() const { return j; }


void Tile::moveRight() {
    auto &grid = game.getGrid();
    int cols = game.getCols();
    const int curI = getI();
    int curJ = getJ();
    int nextJ = curJ + 1;
    for (; nextJ < cols; curJ++, nextJ++, j++) {
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
            delete tile1;
            delete tile2;
        }
    }
};

void Tile::moveLeft() {
    auto &grid = game.getGrid();
    int cols = game.getCols();
    const int curI = getI();
    int curJ = getJ();
    int nextJ = curJ - 1;
    for (; nextJ >= 0; curJ--, nextJ--, j--) {
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
            delete tile1;
            delete tile2;
        }
    }
};

void Tile::moveUp() {
    auto &grid = game.getGrid();
    int rows = game.getRows();
    const int curJ = getJ();
    int curI = getI();
    int nextI = curI - 1;
    for (; nextI >= 0; curI--, nextI--, i--) {
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
            delete tile1;
            delete tile2;
        }
    }
};

void Tile::moveDown(){
    auto &grid = game.getGrid();
    int rows = game.getRows();
    const int curJ = getJ();
    int curI = getI();
    int nextI = curI + 1;
    for (; nextI < rows; curI++, nextI++, i++) {
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
            delete tile1;
            delete tile2;
        }
    }
}


void Tile::draw(sf::RenderWindow& window)
{   
    sf::Text text(game.font);
    
    text.setString(std::to_string(val));
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Black);

    const sf::FloatRect textBounds = text.getLocalBounds();

    text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f
    });

    float x = getX();
    float y = getY();
    shape->setPosition({x, y});
    shape->setFillColor(sf::Color::Green);

   
    const sf::FloatRect shapeBounds = shape->getGlobalBounds();
    text.setPosition({
        shapeBounds.position.x + shapeBounds.size.x / 2.0f,
        shapeBounds.position.y + shapeBounds.size.y / 2.0f
    });

    window.draw(*shape);
    window.draw(text);
}

