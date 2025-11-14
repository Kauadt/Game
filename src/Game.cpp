#include "Game.hpp"
#include <iostream>

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
    while ((int)entities.size() < MAX_ENTITIES)
        spawnEntity();
}

void Game::render()
{
    window.clear(sf::Color::Black);

    for (const auto &e : entities)
        e->draw(window);

    window.display();
}

void Game::spawnEntity()
{
    entities.push_back(std::make_unique<AimEntity>(window));
}
