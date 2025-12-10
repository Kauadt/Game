#pragma once
#include "AimEntity.hpp"

using namespace std;
using namespace sf;

class BombEntity : public AimEntity
{
private:
    bool exploding = false;
    Clock explodeTimer;
    const float EXPLOSION_DURATION = 0.1f;
public:
    BombEntity(sf::Vector2f startPos, sf::Vector2u screenSize);
    bool isClicked(const sf::Vector2f &mousePos) const override;
    void setDead(sf::Vector2f boundPos);
    void explode();
    void update(float dt);
    bool isExploding();
};
