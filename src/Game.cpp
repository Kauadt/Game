#include "Game.hpp"
#include <iostream>

#include <random>

static float randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

Game::Game()
    : window(sf::VideoMode(1000, 600), "Game", sf::Style::Close | sf::Style::Titlebar)
{
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
        {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);

            // remove o item clicado
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

    for (auto &e : entities)
    {
        e->update(dt);
    }

    while ((int)entities.size() < MAX_ENTITIES)
        spawnEntity();
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

    float x = randomFloat(0.f, size.x - 50.f);
    float y = size.y - 50.f; // nasce perto do chão

    sf::Vector2f startPos(x, y);

    entities.push_back(
        std::make_unique<AimEntity>(startPos, size));
}
