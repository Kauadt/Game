#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity/Entity.hpp"
#include "Entity/AimEntity.hpp"
#include <memory>

using namespace std;
using namespace sf;



class Game
{
private:
    sf::RenderWindow window;
    vector<unique_ptr<Entity>> entities;

    const int MAX_ENTITIES = 3;

public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void spawnEntity();
};
