#include "Entity/AimEntity.hpp"
#include <cmath>
#include <random>

static float randomFloat(float a, float b)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(a, b);
    return dist(gen);
}

AimEntity::AimEntity(sf::Vector2f startPos, sf::Vector2u screenSize)
{
    shape.setRadius(20.f);
    shape.setFillColor(sf::Color::Red);

    P0 = startPos;

    P1.x = randomFloat(screenSize.x * 0.2f, screenSize.x * 0.8f);
    P1.y = randomFloat(screenSize.y * 0.4f, screenSize.y * 0.6f);

    P2.x = randomFloat(screenSize.x * 0.1f, screenSize.x * 0.9f);
    P2.y = startPos.y;

    t = 0.f;
    speed = randomFloat(0.3f, 0.6f);
}

void AimEntity::update(float dt)
{
    t += dt * speed;
    if (t > 1.f)
        t = 1.f;

    float u = 1.f - t;

    float x = u * u * P0.x + 2 * u * t * P1.x + t * t * P2.x;
    float y = u * u * P0.y + 2 * u * t * P1.y + t * t * P2.y;

    shape.setPosition({x, y});
}

void AimEntity::draw(sf::RenderWindow &window) const
{
    window.draw(shape);
}

void AimEntity::render(sf::RenderWindow &window)
{
    draw(window);
}

bool AimEntity::isClicked(const sf::Vector2f &mousePos) const
{
    return shape.getGlobalBounds().contains(mousePos);
}

sf::FloatRect AimEntity::getBounds() const
{
    return shape.getGlobalBounds();
}
