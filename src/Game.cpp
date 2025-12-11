#include "Game.hpp"
#include <algorithm>
#include <random>
#include <cmath>
#include <iostream>

using namespace sf;

static float randomFloat(float min, float max)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

Game::Game()
    : window(VideoMode(900, 550), "Game")
{
    backTexture.loadFromFile("assets/texture/fruitBackGround.png");
    backSprite.setTexture(backTexture);

    heartTexture.loadFromFile("assets/texture/heart.png");

    window.setFramerateLimit(60);

    spawnTimer = 0.f;
    nextSpawnDelay = 0.5f;
    isMouseMovedPressed = false;

    font.loadFromFile("assets/fonts/Montserrat-Regular.ttf");
    scoreFont.loadFromFile("assets/fonts/Anton-Regular.ttf");

    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(Color::White);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(10.f, 10.f);

    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(70);
    gameOverText.setFillColor(Color::Yellow);
    gameOverText.setFont(scoreFont);

    FloatRect g = gameOverText.getLocalBounds();
    gameOverText.setOrigin(g.left + g.width / 2.f, g.top + g.height / 2.f);
    gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 120.f);

    highScoreText.setFont(scoreFont);
    highScoreText.setCharacterSize(35);
    highScoreText.setFillColor(Color::White);
    highScoreText.setString("High Score: 0");

    FloatRect hs = highScoreText.getLocalBounds();
    highScoreText.setOrigin(hs.left + hs.width / 2.f, hs.top + hs.height / 2.f);
    highScoreText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 20.f);

    playTexture.loadFromFile("assets/texture/play.png");
    playButton.setTexture(playTexture);
    FloatRect pb = playButton.getLocalBounds();
    playButton.setOrigin(pb.width / 2.f, pb.height / 2.f);
    playButton.setPosition(window.getSize().x / 2.f, 300.f);

    restartTexture.loadFromFile("assets/texture/replay.png");
    restartButton.setTexture(restartTexture);
    FloatRect rb = restartButton.getLocalBounds();
    restartButton.setOrigin(rb.width / 2.f, rb.height / 2.f);
    restartButton.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 80.f);

    screenState = ScreenState::MENU;
}

void Game::resetGame()
{
    entities.clear();
    sliceEntities.clear();
    state.reset();

    for (int i = 0; i < MAX_ENTITIES; i++)
        spawnEntity();

    sliceEntity();
    updateHearts();
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();

        if (screenState == ScreenState::MENU)
        {
            if (event.type == Event::MouseButtonPressed)
            {
                Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                if (playButton.getGlobalBounds().contains(mouse))
                {
                    screenState = ScreenState::PLAYING;
                    resetGame();
                }
            }
            continue;
        }

        if (screenState == ScreenState::GAME_OVER)
        {
            if (event.type == Event::MouseButtonPressed)
            {
                Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                if (restartButton.getGlobalBounds().contains(mouse))
                {
                    screenState = ScreenState::PLAYING;
                    resetGame();
                }
            }
            continue;
        }

        if (event.type == Event::MouseMoved && Mouse::isButtonPressed(Mouse::Left))
            isMouseMovedPressed = true;
        else
            isMouseMovedPressed = false;

        if (isMouseMovedPressed &&
            clkSliceSp.getElapsedTime().asSeconds() >= 0.005f &&
            sliceEntities.size() <= MAX_SLICEENTITIES)
        {
            sliceEntity();
            clkSliceSp.restart();
        }
    }
}

void Game::update()
{
    static Clock clock;
    float dt = clock.restart().asSeconds();

    if (screenState != ScreenState::PLAYING)
        return;

    if (clkSliceDlt.getElapsedTime().asSeconds() >= 0.005f &&
        !isMouseMovedPressed && sliceEntities.size() > 1)
    {
        sliceEntities.pop_back();
        clkSliceDlt.restart();
    }

    if(isMouseMovedPressed == false)
        sliceEntities[0].get()->setPosition(Vector2f(1000.f,1000.f));


    if (!sliceEntities.empty())
    {
        auto &s = sliceEntities.front();

        for (auto &e : entities)
        {
            if (auto f = dynamic_cast<FruitEntity *>(e.get()))
            {
                if (f->getBounds().contains(s->getPosition()) && !f->wasSliced())
                {
                    f->setDead(s->getPosition());
                    state.addScore(10);
                }
            }

            if (auto b = dynamic_cast<BombEntity *>(e.get()))
            {
                if (b->getBounds().contains(s->getPosition()) && !b->isExploding())
                {
                    b->setDead(s->getPosition());

                    highScoreText.setString("High Score: " + to_string(state.getHighScore()));
                    FloatRect hs = highScoreText.getLocalBounds();
                    highScoreText.setOrigin(hs.left + hs.width / 2.f, hs.top + hs.height / 2.f);
                    highScoreText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 20.f);

                    screenState = ScreenState::GAME_OVER;
                }
            }
        }
    }

    entities.erase(
        remove_if(entities.begin(), entities.end(),
                  [&](const unique_ptr<AimEntity> &e)
                  {
                      if (!e->isDead())
                          return false;

                      if (auto f = dynamic_cast<FruitEntity *>(e.get()))
                      {
                          if (!f->wasSliced())
                          {
                              state.loseLife();

                              if (state.isGameOver())
                              {
                                  highScoreText.setString("High Score: " + to_string(state.getHighScore()));
                                  FloatRect hs = highScoreText.getLocalBounds();
                                  highScoreText.setOrigin(hs.left + hs.width / 2.f, hs.top + hs.height / 2.f);
                                  highScoreText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 20.f);

                                  screenState = ScreenState::GAME_OVER;
                              }
                          }
                      }
                      return true;
                  }),
        entities.end());

    for (auto &e : entities)
        e->update(dt);

    if (entities.size() < MAX_ENTITIES)
    {
        spawnTimer += dt;
        if (spawnTimer >= nextSpawnDelay)
        {
            spawnEntity();
            spawnTimer = 0.f;
            nextSpawnDelay = randomFloat(0.5f, 2.f);
        }
    }

    if (isMouseMovedPressed)
    {
        Vector2i p = Mouse::getPosition(window);
        Vector2f mousepos = window.mapPixelToCoords(p);

        float maxDistance = sliceEntities.empty() ? 20.f : sliceEntities[0]->getRad() * 2.f;

        for (size_t i = 0; i < sliceEntities.size(); ++i)
        {
            SliceEntity *curr = sliceEntities[i].get();

            if (i == 0)
                curr->setPosition(mousepos);
            else
            {
                SliceEntity *prev = sliceEntities[i - 1].get();

                Vector2f a = prev->getPosition();
                Vector2f b = curr->getPosition();

                float dx = b.x - a.x;
                float dy = b.y - a.y;
                float dist = sqrt(dx * dx + dy * dy);

                if (dist > maxDistance)
                {
                    dx /= dist;
                    dy /= dist;
                    curr->setPosition(a.x + dx * maxDistance, a.y + dy * maxDistance);
                }
            }
        }
    }

    scoreText.setString(to_string(state.getScore()));

    updateHearts();
}

void Game::render()
{
    window.clear();
    window.draw(backSprite);

    if (screenState == ScreenState::MENU)
    {
        window.draw(playButton);
        window.display();
        return;
    }

    if (screenState == ScreenState::GAME_OVER)
    {
        for (auto &e : entities)
            e->render(window);

        for (auto &s : sliceEntities)
            s->render(window);

        for (auto &h : hearts)
            window.draw(h);

        window.draw(gameOverText);
        window.draw(restartButton);
        window.draw(highScoreText);

        window.display();
        return;
    }

    for (auto &e : entities)
        e->render(window);

    for (auto &s : sliceEntities)
        s->render(window);

    window.draw(scoreText);

    for (auto &h : hearts)
        window.draw(h);

    window.display();
}

void Game::spawnEntity()
{
    Vector2u size = window.getSize();
    float x = randomFloat(50.f, size.x - 50.f);
    Vector2f pos(x, (float)size.y);

    if (randomFloat(0.f, 1.f) < 0.2f)
        entities.push_back(make_unique<BombEntity>(pos, size));
    else
        entities.push_back(make_unique<FruitEntity>(pos, size));
}

void Game::sliceEntity()
{
    sliceEntities.push_back(make_unique<SliceEntity>());
}

void Game::updateHearts()
{
    hearts.clear();

    float spacing = 40.f;
    float margin = 10.f;

    float startX = window.getSize().x - margin - (state.getLives() * spacing);

    for (int i = 0; i < state.getLives(); i++)
    {
        Sprite s;
        s.setTexture(heartTexture);
        s.setScale(1.1f, 1.1f);
        s.setPosition(startX + i * spacing, 10.f);
        hearts.push_back(s);
    }
}
