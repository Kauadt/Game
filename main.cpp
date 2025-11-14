#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

using namespace std;
using namespace sf;

float randomPosition(RenderWindow &window, float radius)
{
    random_device rd;
    mt19937 gen(rd());

    Vector2u windowSize = window.getSize();

    uniform_real_distribution<float> distX(0.f, windowSize.x - (radius * 2));

    return distX(gen);
}

void createCircle(RenderWindow &window, vector<CircleShape> &circles)
{
    Vector2u windowSize = window.getSize();

    CircleShape circle(50.f);

    circle.setFillColor(Color::Blue);

    float randomPosX = randomPosition(window, circle.getRadius());
    float posY = (windowSize.y - (circle.getRadius() * 2));
    circle.setPosition(randomPosX, posY);
    circles.push_back(circle);
}

int main()
{
    RenderWindow window;
    window.create(VideoMode(1000, 600), "Game", Style::Close | Style::Titlebar);

    static vector<CircleShape> circles;
    const int MAX_CIRCLES = 3;

    for (int i = 0; i < MAX_CIRCLES; i++)
    {
        createCircle(window, circles);
    }

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);

                circles.erase(
                    remove_if(circles.begin(), circles.end(),
                              [&](CircleShape &c)
                              {
                                  return c.getGlobalBounds().contains(clickPos);
                              }),
                    circles.end());
            }
        }

        while (circles.size() < MAX_CIRCLES)
        {
            createCircle(window, circles);
        }

        window.clear(Color::Black);
        for (auto &c : circles)
            window.draw(c);
        window.display();
    }
}
