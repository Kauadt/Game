#pragma once
#include "Entity.hpp"

class AimEntity : public Entity
{
private:
    CircleShape shape;

public:
    AimEntity(RenderWindow &window, float radius = 50.f);

    void draw(RenderWindow &renderWindow) const override;
    bool isClicked(const Vector2f &mousePos) const override;
    FloatRect getBounds() const override;
};