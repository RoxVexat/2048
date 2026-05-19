#include "Data.h"

#include "Config.h"

#include <fstream>
#include <cmath>
#include <iostream>

std::vector<int> Data::highScores(10, 0);
void Data::loadHighScores() {
    std::ifstream file("highscores.txt");

    if (!file.is_open()) return;

    int index = 0;    
    std::string line;

    while (index < 10 && std::getline(file, line)) {
        highScores[index] = std::stoi(line);
        index++;
    }
}   

void Data::saveHighScores() {
    std::ofstream file("highscores.txt");
    if (!file.is_open()) return;

    for (int score : highScores) {
        file << score << "\n";
    }
}

void Data::updateHighScore(int score) {
    int dim = g_config.getGridDimension();
    highScores[dim] = std::max(highScores[dim], score);
}