#pragma once

class Config {
    public:

        Config(
            unsigned int windowSize = 800,
            int gridDimension = 4,
            float gapRatio = 0.24f,
            float animTime = 0.1f,
            float timeBeforeGameOver = 1
        );

        unsigned int getWindowSize() const;
        int getGridDimension() const;
        float getGapRatio() const;
        float getAnimTime() const;
        float getTimeBeforeGameOver() const;
        
        int getGridSize() const;
        float getGridOffset() const;
        float getTileSize() const;
        float getGapSize() const;
        float getGridLineWidth() const;
        int getFontSize() const;
    

        void setWindowSize(unsigned int windowSize);
        void setGridSize(int gridSize);
        void setGapRatio(float gapRatio);
        void setAnimTime(float animTime);
        void setGridDimension(int gridDimension);

    private:

        void calculateDerived();

        unsigned int windowSize_;
        float gapRatio_;
        int gridDimension_;
        float animTime_;
        float timeBeforeGameOver_;
        
        int gridSize_;
        float gapSize_;
        float gridOffset_;
        float tileSize_;
        float gridLineWidth_;
        int fontSize_;
};

extern Config g_config;