#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void draw(RenderWindow &renderWindow) const = 0;
    virtual bool isClicked(const Vector2f &mousePos) const = 0;
    virtual FloatRect getBounds() const = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow &window) = 0;
};
