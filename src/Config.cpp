#include "Config.hpp"

Config g_config;

Config::Config
(
    float windowSize,
    float gridSize,
    float gapRatio,
    float animTime,
    int gridDimension
) : windowSize(windowSize),
    gridSize(gridSize),
    gapRatio(gapRatio),
    animTime(animTime),
    gridDimension(gridDimension)
{
    calculateDerived();
};

void Config::calculateDerived()
{
    gridOffset = (windowSize - gridSize) / 2;
    tileSize = gridSize * (1 - gapRatio) / gridDimension;
    gapSize = gridSize * gapRatio / (gridDimension + 1);
    gridLineWidth = gapSize / 4;
    fontSize = static_cast<int>(tileSize * 2/3);
}


float Config::getWindowSize() const { return windowSize; }
float Config::getGridSize() const { return gridSize; }
float Config::getGapRatio() const { return gapRatio; }
float Config::getAnimTime() const { return animTime; }
int Config::getGridDimension() const { return gridDimension; }

float Config::getGridOffset() const { return gridOffset; }
float Config::getTileSize() const { return tileSize; }
float Config::getGapSize() const { return gapSize; }
float Config::getGridLineWidth() const { return gridLineWidth; }
int Config::getFontSize() const { return fontSize; }


void Config::setWindowSize(float newWindowSize) {
    windowSize = newWindowSize;
    calculateDerived();
}

void Config::setGridSize(float newGridSize) {
    gridSize = newGridSize;
    calculateDerived();
}

void Config::setGapRatio(float newGapRatio) {
    gapRatio = newGapRatio;
    calculateDerived();
}

void Config::setAnimTime(float newAnimTime) {
    animTime = newAnimTime;
}

void Config::setGridDimension(int newGridDimension) {
    gridDimension = newGridDimension;
    calculateDerived();
}