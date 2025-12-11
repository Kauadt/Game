#include "GameState.hpp"
#include <fstream>

GameState::GameState()
{
    score = 0;
    lives = 3;
    highScore = 0;
    loadHighScore();
}

void GameState::reset()
{
    score = 0;
    lives = 3;
}

void GameState::addScore(int value)
{
    score += value;
    if (score > highScore)
        highScore = score;
    saveHighScore();
}

void GameState::loseLife()
{
    lives--;
}

long long GameState::getScore() const
{
    return score;
}

int GameState::getLives() const
{
    return lives;
}

long long GameState::getHighScore() const
{
    return highScore;
}

bool GameState::isGameOver() const
{
    return lives <= 0;
}

void GameState::loadHighScore()
{
    std::ifstream file("highscore.dat");
    if (!file.is_open())
    {
        highScore = 0;
        return;
    }

    long long value;
    file >> value;

    if (!file.fail() && value >= 0)
        highScore = value;
    else
        highScore = 0;

    file.close();
}

void GameState::saveHighScore()
{
    std::ofstream file("highscore.dat", std::ios::trunc);
    if (!file.is_open())
        return;

    file << highScore;
    file.close();
}
