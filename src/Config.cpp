#include "Config.h"

Config g_config;

Config::Config
(
    unsigned int windowSize,
    int gridDimension,
    float gapRatio,
    float animTime,
    float timeBeforeGameOver

) : windowSize_(windowSize),
    gridSize_(static_cast<int>(windowSize * 0.8)),
    gapRatio_(gapRatio),
    animTime_(animTime),
    gridDimension_(gridDimension),
    timeBeforeGameOver_(timeBeforeGameOver)
{
    calculateDerived();
};

void Config::calculateDerived()
{
    gridOffset_ = (static_cast<int>(windowSize_) - gridSize_) / 2;
    tileSize_ = gridSize_ * (1 - gapRatio_) / gridDimension_;
    gapSize_ = gridSize_ * gapRatio_ / (gridDimension_ + 1);
    gridLineWidth_ = gapSize_ / 4;
    fontSize_ = static_cast<int>(tileSize_ * 2/3);
}


unsigned int Config::getWindowSize() const { return windowSize_; }
int Config::getGridDimension() const { return gridDimension_; }
float Config::getGapRatio() const { return gapRatio_; }
float Config::getAnimTime() const { return animTime_; }
float Config::getTimeBeforeGameOver() const {return timeBeforeGameOver_; }

int Config::getGridSize() const { return gridSize_; }
float Config::getGridOffset() const { return gridOffset_; }
float Config::getTileSize() const { return tileSize_; }
float Config::getGapSize() const { return gapSize_; }
float Config::getGridLineWidth() const { return gridLineWidth_; }
int Config::getFontSize() const { return fontSize_; }


void Config::setWindowSize(unsigned int newWindowSize) {
    windowSize_ = newWindowSize;
    calculateDerived();
}

void Config::setGridSize(int newGridSize) {
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