#include "Entity/AimEntity.hpp"
#include <random>
#include <cmath>

static float randomFloat(float a, float b)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(a, b);
    return dist(gen);
}

AimEntity::AimEntity(Vector2f startPos, Vector2u screenSize)
{
    dead = false;
    fallingStraight = false;
    fallSpeed = 150.f;

    FloatRect rect = sprite.getLocalBounds();
    sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);

    float radius = sprite.getGlobalBounds().height / 2.f;

    P0 = startPos;
    P0.y = screenSize.y + radius;

    float margin = 50.f;
    float endX;

    do {
        endX = randomFloat(margin, screenSize.x - margin);
    } while (abs(endX - P0.x) < 220.f);

    P2.x = endX;
    P2.y = screenSize.y + radius;

    P1.x = (P0.x + P2.x) / 2.f;

    float y1 = randomFloat(screenSize.y * 0.25f, screenSize.y * 0.50f);
    P1.y = 2.f * y1 - P0.y;

    t = 0.f;
    float duration = randomFloat(3.f, 7.f);
    speed = 1.f / duration;

    sprite.setPosition(P0);
}

void AimEntity::update(float dt)
{
    if (fallingStraight)
    {
        sprite.move(0.f, fallSpeed * dt);
        if (sprite.getPosition().y > 900.f)
            dead = true;
        return;
    }

    t += dt * speed;

    if (t >= 1.f)
    {
        t = 1.f;
        dead = true;
    }

    float u = 1.f - t;
    float uu = u * u;
    float tt = t * t;

    Vector2f pos = (uu * P0) + (2.f * u * t * P1) + (tt * P2);
    sprite.setPosition(pos);
}

void AimEntity::draw(RenderWindow &window) const
{
    window.draw(sprite);
}

void AimEntity::render(RenderWindow &window)
{
    draw(window);
}

FloatRect AimEntity::getBounds() const
{
    return sprite.getGlobalBounds();
}

void AimEntity::setDead(Vector2f pos)
{
    if (sprite.getGlobalBounds().contains(pos))
        dead = true;
}

bool AimEntity::isDead() const
{
    return dead;
}
