#include <Tile.hpp>
#include <Game.hpp>
#include <iostream>

Tile::Tile(Game &game, int i, int j)
    : i(i), j(j),
      shape({static_cast<float>(size), static_cast<float>(size)}){
        game.setTile(*this, i, j);
        game.appendToRenderList(this);
      }

float Tile::getX() const
{
    return (j + 1) * 40 + j * size;
}
float Tile::getY() const
{
    return (i + 1) * 40 + i * size;
}

void Tile::draw(sf::RenderWindow& window)
{   
    float x = getX();
    float y = getY();
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}

int Tile::getI() const
{
    return i;
}

int Tile::getJ() const
{
    return j;
}

void Tile::setGridPos(int i, int j)
{
    this->i = i;
    this->j = j;
}

void Tile::moveRight(Game &game) {
    std::vector<std::optional<Tile>> &grid = game.getGrid();
    int cols = game.getCols();
    const int curI = getI();
    int curJ = getJ();
    int nextJ = curJ + 1;
    for (; nextJ < cols; curJ++, nextJ++, j++) {
        if (!game.hasTile(curI, nextJ)) {
            game.setTile(*this, curI, nextJ);
            game.resetCell(curI, curJ);
        } else break;
    }
};
void Tile::moveLeft(Game &game) {
    std::vector<std::optional<Tile>> &grid = game.getGrid();
    int cols = game.getCols();
    const int curI = getI();
    int curJ = getJ();
    int nextJ = curJ - 1;
    for (; nextJ >= 0; curJ--, nextJ--, j--) {
        if (!game.hasTile(curI, nextJ)) {
            game.setTile(*this, curI, nextJ);
            game.resetCell(curI, curJ);
        } else break;
    }

};
void Tile::moveUp(Game &game) {
    std::vector<std::optional<Tile>> &grid = game.getGrid();
    int rows = game.getRows();
    const int curJ = getJ();
    int curI = getI();
    int nextI = curI - 1;
    for (; nextI >= 0; curI--, nextI--, i--) {
        if (!game.hasTile(nextI, curJ)) {
            game.setTile(*this, nextI, curJ);
            game.resetCell(curI, curJ);
        } else break;
    }

};
void Tile::moveDown(Game &game){
    std::vector<std::optional<Tile>> &grid = game.getGrid();
    int rows = game.getRows();
    const int curJ = getJ();
    int curI = getI();
    int nextI = curI + 1;
    for (; nextI < rows; curI++, nextI++, i++) {
        if (!game.hasTile(nextI, curJ)) {
            game.setTile(*this, nextI, curJ);
            game.resetCell(curI, curJ);
        } else break;
    }
};

