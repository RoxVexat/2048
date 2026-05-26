#include "Game.h"

#include "Tile.h"
#include "Config.h"
#include "Data.h"

#include <algorithm>
#include <iostream>
#include <random>


sf::Font Game::font("arial.ttf");

Game::Game()
    : rows_(g_config.getGridDimension()),
      cols_(g_config.getGridDimension()),
      grid_(rows_ * cols_),
      animTimePassed(g_config.getAnimTime()),
      shouldDrawGameOver_(false),
      timePassedSinceGameOver_(0.0f),
      areTilesMoving(false),
      score(0),
      sceneBuffer_({g_config.getWindowSize(), g_config.getWindowSize()})

{   
    static_cast<void>(blur_.loadFromFile("blur.frag", sf::Shader::Type::Fragment));
    blur_.setUniform("blur_radius", 15.0f);
    blur_.setUniform("texture", sf::Shader::CurrentTexture);

    generateRandomTile();
    generateRandomTile();
}

Game::~Game()
{
    cleanUp();
}

int Game::getRows() const { return rows_; }
int Game::getCols() const { return cols_; }
int Game::getNumTiles() const
{
    int numTiles = 0;
    for (auto tile : grid_) {
        if (tile)
            numTiles++;
    }
    return numTiles;
}
const std::vector<Tile *> &Game::getGrid() const { return grid_; }
const std::vector<Tile *> &Game::getRenderList() const { return renderList_; }
Tile *Game::getCell(int i, int j) const
{
    return grid_[i * cols_ + j];
}

std::vector<Tile *>& Game::getGrid() { return grid_; }
std::vector<Tile *>& Game::getRenderList() { return renderList_; }
sf::RenderTexture& Game::getSceneBuffer() { return sceneBuffer_; }

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
                {
                    return true;
                }
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
                {
                    return true;
                }
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
                {
                    return true;
                }
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
                {
                    return true;
                }
                    
            }
        }
    }
    return false;
}

void Game::resetGridCell(int i, int j)
{
    grid_[i * cols_ + j] = nullptr;
}

void Game::generateRandomTile()
{

    if (gameOver() && getNumTiles() > 2)
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

void Game::makeTilesOld() {
    for (auto &tile : grid_)
    {   
        if (tile) 
        {
            tile->isNewTile = false;
        }
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
            {
                tile->moveLeft();
            }
        }
    }
    makeTilesOld();
    Data::updateHighScore(score);
    Data::saveHighScores();
}

void Game::moveRight()
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = cols_ - 1; j >= 0; j--)
        {
            auto tile = getCell(i, j);
            if (tile) 
            {
                tile->moveRight();
            }
        }
    }
    makeTilesOld();
    Data::updateHighScore(score);
    Data::saveHighScores();
}

void Game::moveUp()
{
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            auto tile = getCell(i, j);
            if (tile)
            {
                tile->moveUp();
            }
        }
    }
    makeTilesOld();
    Data::updateHighScore(score);
    Data::saveHighScores();
}

void Game::moveDown()
{
    for (int i = rows_ - 1; i >= 0; i--)
    {
        for (int j = 0; j < cols_; j++)
        {
            auto tile = getCell(i, j);
            if (tile)
            {
                tile->moveDown();
            }
                
        }
    }
    makeTilesOld();
    Data::updateHighScore(score);
    Data::saveHighScores();
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
}

void Game::cleanUp()
{
    for (auto tile : renderList_)
    {
        delete tile;
    }
        
    renderList_.clear();

    for (auto &ptr : grid_)
    {
        ptr = nullptr;
    }
}

void Game::reset()
{
    cleanUp();

    score = 0;
    shouldDrawGameOver_ = false;
    timePassedSinceGameOver_ = 0;

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

    if (!shouldDrawGameOver_ && gameOver()) {
        timePassedSinceGameOver_ += deltaTime;
        if (timePassedSinceGameOver_ >= g_config.getTimeBeforeGameOver())
            shouldDrawGameOver_ = true;
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
    sceneBuffer_.clear(sf::Color::Black);
    
    renderGridBackground();    
    for (auto tile : renderList_)
    {
        tile->render();
    }

    sceneBuffer_.display();
    sf::Sprite sceneSprite(sceneBuffer_.getTexture()); 
    
    if (shouldDrawGameOver_) {
        window.draw(sceneSprite, &blur_);
        drawGameOver(window);
    } else {
        window.draw(sceneSprite);
    }

    drawGameInfo(window);
}

void Game::renderGridBackground()
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
    sceneBuffer_.draw(bg);

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

        sceneBuffer_.draw(vLine);
        sceneBuffer_.draw(hLine);
    }
}

void Game::drawGameInfo(sf::RenderWindow& window)
{
    const int dim = g_config.getGridDimension();
    const int best = Data::highScores[dim];

    sf::Text text(font);

    std::ostringstream info;
    info << dim << "x" << dim
         << " | " << "Score: " << score
         << "  Best: " << best;

    text.setString(info.str());
    text.setCharacterSize(30 * g_config.getWindowSize() / 800);
    text.setFillColor(sf::Color::White);
    text.setPosition({4, 0});

    window.draw(text);
}

void Game::drawGameOver(sf::RenderWindow& window)
{
    const int windowSize = g_config.getWindowSize();
    const float rectWidth = static_cast<int>(windowSize / 800 * 360);
    const float rectHeight = static_cast<int>(windowSize / 800 * 210);
    const float rectX = windowSize/2 - rectWidth/2;
    const float rectY = windowSize/2 - rectHeight/2;
    const int textSize = windowSize / 800 * 62;

    sf::RectangleShape rect({rectWidth, rectHeight});

    rect.setFillColor(sf::Color::Black);
    rect.setPosition({rectX, rectY});

    sf::Text text1(font);
    sf::Text text2(font);

    text1.setString("Game Over");
    text1.setFillColor(sf::Color::White);
    text1.setCharacterSize(textSize);
    text2.setString("Restart? (R)");
    text2.setFillColor(sf::Color::White);
    text2.setCharacterSize(textSize);

    sf::FloatRect textRect1 = text1.getLocalBounds();
    text1.setOrigin({
        textRect1.size.x / 2.0f,
        textRect1.size.y / 2.0f
    });
    text1.setPosition({
        rectX + rectWidth / 2.0f,
        rectY + textSize / 2.0f
    });

    sf::FloatRect textRect2 = text2.getLocalBounds();
    text2.setOrigin({
        textRect2.size.x / 2.0f,
        textRect2.size.y / 2.0f
    });
    text2.setPosition({
        rectX + rectWidth / 2.0f,
        rectY + rectHeight - 6.0f / 5 * textSize
    });

    window.draw(rect);
    window.draw(text1);
    window.draw(text2);
}