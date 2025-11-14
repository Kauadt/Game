#include "Entity/AimEntity.hpp"
#include <random>

using namespace std;

static float randomX(sf::RenderWindow &window, float radius) {
    random_device rd;
    mt19937 gen(rd());
    auto size = window.getSize();
    uniform_real_distribution<float> dist(0.f, size.x - radius * 2);
    return dist(gen);
}

AimEntity::AimEntity(sf::RenderWindow &window, float radius) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);

    float x = randomX(window, radius);
    float y = window.getSize().y - radius * 2;

    shape.setPosition({x, y});
}

void AimEntity::draw(sf::RenderWindow &window) const {
    window.draw(shape);
}

bool AimEntity::isClicked(const sf::Vector2f &mousePos) const {
    return shape.getGlobalBounds().contains(mousePos);
}

sf::FloatRect AimEntity::getBounds() const {
    return shape.getGlobalBounds();
}
