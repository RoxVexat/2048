#include <vector>

class Data {
    public:
        static std::vector<int> highScores;

        static void loadHighScores();
        static void saveHighScores();

        static void updateHighScore(int score);
};