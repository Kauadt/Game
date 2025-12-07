#include "Game.hpp"
#include "Entity/AimEntity.hpp"
#include <iostream>
#include <algorithm>
#include <random>

static float randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

Game::Game()
    : window(sf::VideoMode(900, 550), "Game", sf::Style::Close | sf::Style::Titlebar)
{
    window.setFramerateLimit(60);

    spawnTimer = 0.f;
    nextSpawnDelay = 0.5f; // Delay inicial curto

    // Inicializa com algumas entidades ou deixe vazio para o timer preencher
    for (int i = 0; i < MAX_ENTITIES; i++)
        spawnEntity();
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f clickPos((float)event.mouseButton.x, (float)event.mouseButton.y);

            // Remove se clicar
            entities.erase(
                std::remove_if(entities.begin(), entities.end(),
                               [&](const std::unique_ptr<Entity> &e)
                               {
                                   return e->isClicked(clickPos);
                               }),
                entities.end());
        }
    }
}

void Game::update()
{
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();

    // 1. Atualiza Posição
    for (auto &e : entities)
    {
        e->update(dt);
    }

    // 2. Remove entidades mortas (que completaram o trajeto)
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
                       [](const std::unique_ptr<Entity> &e)
                       {
                           return e->isDead();
                       }),
        entities.end());

    // 3. SPAWN COM DELAY
    // Se há espaço para mais entidades...
    if (entities.size() < MAX_ENTITIES)
    {
        spawnTimer += dt; // Conta o tempo

        // Só cria se o tempo passou do delay estipulado
        if (spawnTimer >= nextSpawnDelay)
        {
            spawnEntity();
            
            spawnTimer = 0.f; // Reseta timer
            // Define o próximo delay aleatório (ex: entre 0.5s e 1.5s)
            nextSpawnDelay = randomFloat(0.5f, 2.f); 
        }
    }
}

void Game::render()
{
    window.clear();
    for (auto &e : entities)
        e->render(window);
    window.display();
}

void Game::spawnEntity()
{
    sf::Vector2u size = window.getSize();
    float x = randomFloat(50.f, size.x - 50.f);
    // Y é tratado no AimEntity, mas passamos size para referência
    
    sf::Vector2f startPos(x, (float)size.y);
    entities.push_back(std::make_unique<AimEntity>(startPos, size));
}