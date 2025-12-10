#include "Entity/AimEntity.hpp"
#include <cmath>
#include <random>

// Função auxiliar interna
static float randomFloat(float a, float b)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(a, b);
    return dist(gen);
}


// PODE TER DADO ERRO NA QUEDA LIVRE!!!!!!!!!!!!!!!!!!!!
AimEntity::AimEntity(sf::Vector2f startPos, sf::Vector2u screenSize)
{
    FloatRect textureRect = sprite.getLocalBounds();

    sprite.setOrigin(textureRect.width / 2.f , textureRect. height / 2.f);

    // Inicializa flag de morte
    dead = false;

    float entityRadius = sprite.getGlobalBounds().height / 2.f;

    // --- 1. Ponto Inicial (P0) ---
    P0 = startPos;
    P0.y = screenSize.y + entityRadius; // Nasce logo abaixo da tela

    // --- 2. Ponto Final (P2) ---
    float margin = 50.f;
    float minX = margin;
    float maxX = screenSize.x - margin;
    float endX;

    // Garante que o destino X esteja longe da origem X
    do {
        endX = randomFloat(minX, maxX);
    } while (std::abs(endX - P0.x) < 220.f);

    P2.x = endX;
    P2.y = screenSize.y + entityRadius; // Cai na mesma altura que nasceu

    // --- 3. Ponto de Controle (P1 - O Pico) ---
    P1.x = (P0.x + P2.x) / 2.f;

    // Altura aleatória entre 15% (alto) e 60% (médio) da tela
    float maxPeakY = screenSize.y * 0.25f; 
    float minPeakY = screenSize.y * 0.50f;
    float targetPeakY = randomFloat(maxPeakY, minPeakY);

    P1.y = 2.f * targetPeakY - P0.y;

    // --- 4. Velocidade baseada em Duração ---
    t = 0.f;
    float duration = randomFloat(3.f, 7.f); 
    speed = 1.0f / duration;

    // Define a posição inicial imediatamente para evitar que apareça em (0,0)
    // por 1 frame antes do primeiro update.
    sprite.setPosition(P0);
}


// PODE TER DADO ERRO NA QUEDA LIVRE!!!!!!!!!!!!!!!!!!!!
void AimEntity::update(float dt)
{
    // Incrementa t
    t += dt * speed;

    // Verifica se chegou ao final da curva
    if (t >= 1.0f)
    {
        t = 1.0f;
        dead = true; // Marca para destruição natural
    }

    // Cálculo da Curva de Bézier Quadrática
    float u = 1.f - t;
    float uu = u * u;
    float tt = t * t;

    sf::Vector2f currentPos = (uu * P0) + (2.f * u * t * P1) + (tt * P2);

    sprite.setPosition(currentPos);
}

void AimEntity::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

void AimEntity::render(sf::RenderWindow &window)
{
    draw(window);
}


// PODE TER DADO ERRO NA QUEDA LIVRE!!!!!!!!!!!!!!!!!!!!
sf::FloatRect AimEntity::getBounds() const
{
    return sprite.getGlobalBounds();
}

void AimEntity::setDead(Vector2f boundPos) {

    FloatRect thisBound = sprite.getGlobalBounds(); 
    if(thisBound.contains(boundPos)){
        dead = true;
    }
}

bool AimEntity::isDead() const
{
    return dead;
}