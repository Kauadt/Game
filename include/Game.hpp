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
    RenderWindow window;

    Texture backTexture;
    Sprite backSprite;

    vector<unique_ptr<AimEntity>> entities;
    vector<unique_ptr<SliceEntity>> sliceEntities;

    Clock clkSliceSp;
    Clock clkSliceDlt;

    float spawnTimer;
    float nextSpawnDelay;
    bool isMouseMovedPressed;

    GameState state;
    Font font;
    Font scoreFont;
    Text scoreText;

    ScreenState screenState;

    Texture playTexture;
    Sprite playButton;

    Texture restartTexture;
    Sprite restartButton;

    Text gameOverText;
    Text highScoreText;

    Texture heartTexture;
    vector<Sprite> hearts;

    void processEvents();
    void update();
    void render();
    void spawnEntity();
    void sliceEntity();
    void resetGame();
    void updateHearts();

public:
    Game();
    void run();
};
