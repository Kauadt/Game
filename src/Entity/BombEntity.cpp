#include "Entity/BombEntity.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;


BombEntity::BombEntity(sf::Vector2f startPos, sf::Vector2u screenSize)
    : AimEntity(startPos, screenSize)
{
    if(!texture.loadFromFile("assets/bomb.png")){
        cout<< "erro ao carregar sprite"<< endl;
    }
    sprite.setTexture(texture);
}

bool BombEntity::isClicked(const sf::Vector2f &mousePos) const
{
     FloatRect bounds = sprite.getGlobalBounds();
    Vector2f center = {
        bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f
    };

    float radius = bounds.width / 2.0f;

    float dx = center.x - mousePos.x;
    float dy = center.y - mousePos.y;

    return (dx * dx + dy * dy) <= (radius * radius);
}

void BombEntity::setDead(sf::Vector2f boundPos)
{
    if (sprite.getGlobalBounds().contains(boundPos)){
       if(!texture.loadFromFile("assets/bomb-explode.png")){
        cout<< "erro ao carregar sprite"<< endl;
        }
        sprite.setTexture(texture);

        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setPosition(boundPos);

        exploding = true;
        explodeTimer.restart();

        dead = false;
    }
}

void BombEntity::explode(){
    if(!texture.loadFromFile("assets/bomb-explode.png")){
        cout<< "erro ao carregar sprite"<< endl;
        }
    sprite.setTexture(texture);

}

void BombEntity::update(float dt)
{
    
    if (exploding)
    {
        if (explodeTimer.getElapsedTime().asSeconds() >= EXPLOSION_DURATION)
        {
            dead = true;
        }
    }
    else
    {
        AimEntity::update(dt);
    }
}

bool BombEntity::isExploding(){
    return this->exploding;
}