#pragma once
#include <string>

class GameState
{
private:
    long long score;
    int lives;
    long long highScore;

public:
    GameState();

    void reset();
    void addScore(int value);
    void loseLife();

    long long getScore() const;
    int getLives() const;
    long long getHighScore() const;

    bool isGameOver() const;

    void loadHighScore();
    void saveHighScore();
};
