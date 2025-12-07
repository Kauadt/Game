#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Entity/Entity.hpp"

#define MAX_ENTITIES 5 

class Game
{
private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<Entity>> entities;

    // Variáveis para controle de spawn com delay
    float spawnTimer;
    float nextSpawnDelay;

    void processEvents();
    void update();
    void render();
    void spawnEntity();

public:
    Game();
    void run();
};