#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Entity/FruitEntity.hpp"
#include "Entity/BombEntity.hpp"
#include "Entity/SliceEntity.hpp"
#include "GameState.hpp"

using namespace std;
using namespace sf;

#define MAX_ENTITIES 5
#define MAX_SLICEENTITIES 50

enum class ScreenState
{
    MENU,
    PLAYING,
    GAME_OVER
};

class Game
{
private:
    sf::RenderWindow window;

    Texture backTexture;
    Sprite backSprite;

    std::vector<std::unique_ptr<AimEntity>> entities;
    std::vector<std::unique_ptr<SliceEntity>> sliceEntities;

    sf::Clock clkSliceSp;
    sf::Clock clkSliceDlt;

    float spawnTimer;
    float nextSpawnDelay;
    bool isMouseMovedPressed;

    GameState state;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;

    ScreenState screenState;

    sf::RectangleShape playButton;
    sf::Text playText;

    sf::RectangleShape restartButton;
    sf::Text restartText;

    sf::Text gameOverText;
    sf::Text highScoreText;

    void processEvents();
    void update();
    void render();
    void spawnEntity();
    void sliceEntity();
    void resetGame();

public:
    Game();
    void run();
};
