#include "Entity/FruitEntity.hpp"
#include <cmath>
#include<iostream>



using namespace std;
using namespace sf;

const vector<std::string> FruitEntity::ALL_FRUITS = 
    {"assets/banana.png", "assets/apple.png", "assets/watermelon.png", "assets/orange.png"};

const vector<std::string> FruitEntity::ALL_FRUITS_SLICED = 
    {"assets/banana-cut.png", "assets/apple-cut.png", "assets/watermelon-cut.png", "assets/orange-cut.png"};

FruitEntity::FruitEntity(sf::Vector2f startPos, sf::Vector2u screenSize)
: AimEntity(startPos, screenSize)
{
    sliced = false;

    int qntFrutas = FruitEntity::ALL_FRUITS.size();

    this->fruit = rand() % qntFrutas;
    
    if(!texture.loadFromFile(FruitEntity::ALL_FRUITS[this->fruit])){
        cout << "Erro ao carregar imagem: " << FruitEntity::ALL_FRUITS[this->fruit] << endl;
    }

    sprite.setTexture(texture);
    
}


// PODE TER DADO ERRO NA QUEDA LIVRE!!!!!!!!!!!!!!!!!!!!
bool FruitEntity::isClicked(const sf::Vector2f &mousePos) const
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


// PODE TER DADO ERRO NA QUEDA LIVRE!!!!!!!!!!!!!!!!!!!!
void FruitEntity::setDead(sf::Vector2f pos)
{
    if (sprite.getGlobalBounds().contains(pos))
    {
        sliced = true;

        fallingStraight = true; 
        dead = false;  
        
        if(!texture.loadFromFile(ALL_FRUITS_SLICED[fruit])){
        cout<<"erro ao carregar imagem"<<endl;
        }

        sprite.setTexture(texture);
    }
}

bool FruitEntity::wasSliced() const
{
    return sliced;
}
