#pragma once

class Config {
    public:

        Config(
            unsigned int windowSize = 800,
            float gridSize = 640,
            float gapRatio = 0.24f,
            float animTime = 0.1f,
            int gridDimension = 4
        );

        unsigned int getWindowSize() const;
        float getGridSize() const;
        float getGapRatio() const;
        float getAnimTime() const;
        int getGridDimension() const;
    
        float getGridOffset() const;
        float getTileSize() const;
        float getGapSize() const;
        float getGridLineWidth() const;
        int getFontSize() const;
    

        void setWindowSize(unsigned int windowSize);
        void setGridSize(float gridSize);
        void setGapRatio(float gapRatio);
        void setAnimTime(float animTime);
        void setGridDimension(int gridDimension);

    private:

        void calculateDerived();

        unsigned int windowSize_;
        float gridSize_;
        float gapRatio_;
        int gridDimension_;
        
        float gridOffset_;
        float tileSize_;
        float gapSize_;
        float gridLineWidth_;
        float animTime_;
        int fontSize_;
};

extern Config g_config;