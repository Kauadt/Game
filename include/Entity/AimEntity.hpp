#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class AimEntity : public Entity
{
private:
    sf::CircleShape shape;

    // Parâmetros da trajetória Bézier
    sf::Vector2f P0; // ponto inicial
    sf::Vector2f P1; // pico (control point)
    sf::Vector2f P2; // ponto final

    float t;     // parâmetro da curva, vai de 0 a 1
    float speed; // controla a velocidade

public:
    // Construtor recebe posição inicial e tamanho da tela
    AimEntity(sf::Vector2f startPos, sf::Vector2u screenSize);

    // Implementações obrigatórias da classe Entity
    void update(float dt) override;
    void draw(sf::RenderWindow &window) const override;
    void render(sf::RenderWindow &window) override;

    bool isClicked(const sf::Vector2f &mousePos) const override;
    sf::FloatRect getBounds() const override;
};
