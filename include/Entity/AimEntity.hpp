#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class AimEntity : public Entity
{
private:
    sf::CircleShape shape;

    // Parâmetros da trajetória Bézier
    sf::Vector2f P0; // ponto inicial
    sf::Vector2f P1; // pico (control point)
    sf::Vector2f P2; // ponto final

    float t;     // parâmetro da curva (0 a 1)
    float speed; // velocidade do incremento de t
    bool dead;   // flag para saber se chegou ao fim

public:
    AimEntity(sf::Vector2f startPos, sf::Vector2u screenSize);

    void update(float dt) override;
    void draw(sf::RenderWindow &window) const override;
    void render(sf::RenderWindow &window) override;

    bool isClicked(const sf::Vector2f &mousePos) const override;
    sf::FloatRect getBounds() const override;
    bool isDead() const override;
};