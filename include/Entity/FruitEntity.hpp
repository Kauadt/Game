#pragma once
#include "AimEntity.hpp"

using namespace std;
using namespace sf;

class FruitEntity : public AimEntity
{
private:
    bool sliced;

    static const vector<std::string> ALL_FRUITS;
    static const vector<std::string> ALL_FRUITS_SLICED;
    int fruit;

public:
    FruitEntity(sf::Vector2f startPos, sf::Vector2u screenSize);

    bool isClicked(const sf::Vector2f &mousePos) const override;
    void setDead(sf::Vector2f pos);

    bool wasSliced() const;
};
