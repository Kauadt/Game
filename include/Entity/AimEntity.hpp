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
    sf::Vector2f P0;
    sf::Vector2f P1;
    sf::Vector2f P2;
    float t;
    float speed;
    bool dead;

    bool fallingStraight;
    float fallSpeed;

public:
    AimEntity(sf::Vector2f startPos, sf::Vector2u screenSize);

    void update(float dt) override;
    void draw(sf::RenderWindow &window) const override;
    void render(sf::RenderWindow &window) override;

    sf::FloatRect getBounds() const override;
    bool isDead() const override;
    void setDead(Vector2f boundPos);
};
