#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

#define MAX_SPEED 15

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x = " << event.x << ", y = " << event.y << std::endl;
    mousePosition = {float(event.x),
                     float(event.y)};
}

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void setAngleLimit(float &angle, float maxRotate)
{
    float minRotate = 0 - maxRotate;
    angle = std::max(minRotate, angle);
    angle = std::min(maxRotate, angle);
}

float getDeltaAngle(float arrawAngle, float mouseAngle)
{
    if (mouseAngle < 0)
    {
        mouseAngle += 360;
    }
    float deltaAngle = mouseAngle - arrawAngle;
    if ((deltaAngle < -180) || (deltaAngle > 180))
    {
        deltaAngle = arrawAngle - mouseAngle;
    }

    return deltaAngle;
}

float getRotation(float arrawAngle, float mouseAngle, float maxRotate)
{
    float deltaAngle = getDeltaAngle(arrawAngle, mouseAngle);
    setAngleLimit(deltaAngle, maxRotate);
    float rotation = arrawAngle + deltaAngle;
    if (rotation < 0)
    {
        rotation += 360;
    }

    return rotation;
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float deltaTime)
{
    const float maxRotate = deltaTime * MAX_SPEED;
    float arrawAngle = pointer.getRotation();
    const sf::Vector2f deltaPosition = mousePosition - pointer.getPosition();
    float mouseAngle = toDegrees(atan2(deltaPosition.y, deltaPosition.x));
    float rotation = getRotation(arrawAngle, mouseAngle, maxRotate);

    pointer.setRotation(rotation);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    sf::Clock clock;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, deltaTime);
        redrawFrame(window, pointer);
    }
}