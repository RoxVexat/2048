#pragma once

class Config {
    public:

        Config(
            float windowSize = 800,
            float gridSize = 640,
            float gapRatio = 0.24f,
            float animTime = 0.1f,
            int gridDimension = 4
        );

        float getWindowSize() const;
        float getGridSize() const;
        float getGapRatio() const;
        float getAnimTime() const;
        int getGridDimension() const;
    
        float getGridOffset() const;
        float getTileSize() const;
        float getGapSize() const;
        float getGridLineWidth() const;
        int getFontSize() const;
    

        void setWindowSize(float windowSize);
        void setGridSize(float gridSize);
        void setGapRatio(float gapRatio);
        void setAnimTime(float animTime);
        void setGridDimension(int gridDimension);

    private:

        void calculateDerived();

        float windowSize;
        float gridSize;
        float gapRatio;
        int gridDimension;
        
        float gridOffset;
        float tileSize;
        float gapSize;
        float gridLineWidth;
        float animTime;
        int fontSize;
};

extern Config g_config;