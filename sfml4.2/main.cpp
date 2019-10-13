#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

#define MAX__ANGLE_SPEED 90
#define MAX_SPEED 20

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

void init(sf::ConvexShape &arrow)
{
    arrow.setPointCount(7);
    arrow.setPoint(0, {0, 0});
    arrow.setPoint(1, {-50, 40});
    arrow.setPoint(2, {-50, 20});
    arrow.setPoint(3, {-100, 20});
    arrow.setPoint(4, {-100, -20});
    arrow.setPoint(5, {-50, -20});
    arrow.setPoint(6, {-50, -40});
    arrow.setPosition({400, 300});
    arrow.setFillColor(sf::Color(0xFF, 0x80, 0x00));
    arrow.setOutlineColor(sf::Color(0, 0, 0));
    arrow.setOutlineThickness(2);
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

float getPosition(sf::Vector2f &mousePosition, const float maxSpeed)
{
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float deltaTime)
{
    const float maxRotate = deltaTime * MAX__ANGLE_SPEED;
    const float maxSpeed = deltaTime * MAX_SPEED;
    float arrawAngle = pointer.getRotation();
    const sf::Vector2f deltaPosition = mousePosition - pointer.getPosition();
    float mouseAngle = toDegrees(atan2(deltaPosition.y, deltaPosition.x));
    float rotation = getRotation(arrawAngle, mouseAngle, maxRotate);

    sf::Vector2f motion = mousePosition - pointer.getPosition();
    sf::Vector2f direction;
    direction.x = motion.x / sqrt(pow(motion.x, 2) + pow(motion.y, 2));
    direction.y = motion.y / sqrt(pow(motion.x, 2) + pow(motion.y, 2));
    float speed = MAX_SPEED * deltaTime;
    sf::Vector2f position = pointer.getPosition() + direction * speed;

    pointer.setRotation(rotation);
    pointer.setPosition(position);
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