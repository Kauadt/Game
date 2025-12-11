#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class AimEntity : public Entity
{
protected:
    Texture texture;
    Sprite sprite;
    Vector2f P0;
    Vector2f P1;
    Vector2f P2;
    float t;
    float speed;
    bool dead;
    bool fallingStraight;
    float fallSpeed;

public:
    AimEntity(Vector2f startPos, Vector2u screenSize);

    void update(float dt) override;
    void draw(RenderWindow &window) const override;
    void render(RenderWindow &window) override;

    FloatRect getBounds() const override;
    bool isDead() const override;
    void setDead(Vector2f boundPos);
};
