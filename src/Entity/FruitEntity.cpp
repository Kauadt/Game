#include "Entity/FruitEntity.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;

const vector<string> FruitEntity::ALL_FRUITS =
    {"assets/texture/banana.png", "assets/texture/apple.png", "assets/texture/watermelon.png", "assets/texture/orange.png"};

const vector<string> FruitEntity::ALL_FRUITS_SLICED =
    {"assets/texture/banana-cut.png", "assets/texture/apple-cut.png", "assets/texture/watermelon-cut.png", "assets/texture/orange-cut.png"};

FruitEntity::FruitEntity(Vector2f startPos, Vector2u screenSize)
: AimEntity(startPos, screenSize)
{
    sliced = false;

    fruit = rand() % ALL_FRUITS.size();
    texture.loadFromFile(ALL_FRUITS[fruit]);
    sprite.setTexture(texture);
}

bool FruitEntity::isClicked(const Vector2f &mousePos) const
{
    FloatRect bounds = sprite.getGlobalBounds();
    Vector2f center(bounds.left + bounds.width / 2.f,
                    bounds.top + bounds.height / 2.f);
    float r = bounds.width / 2.f;

    float dx = center.x - mousePos.x;
    float dy = center.y - mousePos.y;

    return (dx * dx + dy * dy) <= (r * r);
}

void FruitEntity::setDead(Vector2f pos)
{
    if (sprite.getGlobalBounds().contains(pos))
    {
        sliced = true;
        fallingStraight = true;
        dead = false;
        texture.loadFromFile(ALL_FRUITS_SLICED[fruit]);
        sprite.setTexture(texture);
    }
}

bool FruitEntity::wasSliced() const
{
    return sliced;
}
