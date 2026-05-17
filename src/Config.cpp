#include "Config.hpp"

Config g_config;

Config::Config
(
    unsigned int windowSize,
    float gridSize,
    float gapRatio,
    float animTime,
    int gridDimension
) : windowSize_(windowSize),
    gridSize_(gridSize),
    gapRatio_(gapRatio),
    animTime_(animTime),
    gridDimension_(gridDimension)
{
    calculateDerived();
};

void Config::calculateDerived()
{
    gridOffset_ = (windowSize_ - gridSize_) / 2;
    tileSize_ = gridSize_ * (1 - gapRatio_) / gridDimension_;
    gapSize_ = gridSize_ * gapRatio_ / (gridDimension_ + 1);
    gridLineWidth_ = gapSize_ / 4;
    fontSize_ = static_cast<int>(tileSize_ * 2/3);
}


unsigned int Config::getWindowSize() const { return windowSize_; }
float Config::getGridSize() const { return gridSize_; }
float Config::getGapRatio() const { return gapRatio_; }
float Config::getAnimTime() const { return animTime_; }
int Config::getGridDimension() const { return gridDimension_; }

float Config::getGridOffset() const { return gridOffset_; }
float Config::getTileSize() const { return tileSize_; }
float Config::getGapSize() const { return gapSize_; }
float Config::getGridLineWidth() const { return gridLineWidth_; }
int Config::getFontSize() const { return fontSize_; }


void Config::setWindowSize(unsigned int newWindowSize) {
    windowSize_ = newWindowSize;
    calculateDerived();
}

void Config::setGridSize(float newGridSize) {
    gridSize_ = newGridSize;
    calculateDerived();
}

void Config::setGapRatio(float newGapRatio) {
    gapRatio_ = newGapRatio;
    calculateDerived();
}

void Config::setAnimTime(float newAnimTime) {
    animTime_ = newAnimTime;
}

void Config::setGridDimension(int newGridDimension) {
    gridDimension_ = newGridDimension;
    calculateDerived();
}