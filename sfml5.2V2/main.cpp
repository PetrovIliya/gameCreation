#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#define BALL_SIZE 30
#define QUANTITY_OF_BALLS 10


constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

void initColors(std::vector<sf::Color> &colors)
{
    colors.push_back(sf::Color(0xFF, 0xFF, 0xFF));
    colors.push_back(sf::Color::Yellow);
    colors.push_back(sf::Color::Red);
    colors.push_back(sf::Color::Green);
    colors.push_back(sf::Color::Blue);
    colors.push_back(sf::Color::Magenta);
    colors.push_back(sf::Color::Cyan);
}

void initBalls(std::vector<sf::CircleShape> &balls, std::vector<sf::Color> &colors)
{
    for (int i = 0; i < QUANTITY_OF_BALLS; i++)
    {
        sf::CircleShape ball(BALL_SIZE);
        float x = std::rand() % 700 + 100;
        float y = std::rand() % 500 + 0;
        sf::Color randColor = colors[std::rand() % 7 + 0];
        sf::Vector2f position = {x, y};
        ball.setFillColor(randColor);
        ball.setPosition(position);
        balls.push_back(ball);
    }
}

void repulsionHandler(std::vector<sf::CircleShape> &balls, std::vector<sf::Vector2f> &speed)
{
    constexpr size_t SIZE = QUANTITY_OF_BALLS;
    for (size_t fi = 0; fi < SIZE; ++fi)
    {
        sf::Vector2f position1 = balls[fi].getPosition();        
        for (size_t si = fi + 1; si < SIZE; ++si)
        {
            sf::Vector2f position2 = balls[si].getPosition();
            sf::Vector2f deltaPosition = position1 - position2;
            float deltaVector = sqrt(pow(deltaPosition.x, 2)  + pow(deltaPosition.y, 2));
            if (deltaVector <= 2 * BALL_SIZE)
            {
                sf::Vector2f deltaPosition1 = position1 - position2;
                sf::Vector2f deltaPosition2 = position2 - position1;
                sf::Vector2f deltaSpeed1 = speed[si] - speed[fi];
                sf::Vector2f deltaSpeed2 = speed[fi] - speed[si];
                float module1 = sqrt(pow(deltaPosition1.x, 2) + pow(deltaPosition1.y, 2)) + sqrt(pow(deltaPosition1.x, 2) + pow(deltaPosition1.y, 2));
                float module2 = sqrt(pow(deltaPosition2.x, 2) + pow(deltaPosition2.y, 2)) + sqrt(pow(deltaPosition2.x, 2) + pow(deltaPosition2.y, 2));;
                float dot1 = deltaSpeed1.x * deltaPosition1.x + deltaSpeed1.y * deltaPosition1.y;
                float dot2 = deltaSpeed2.x * deltaPosition2.x + deltaSpeed2.y * deltaPosition2.y;
                sf::Vector2f direction1 = deltaSpeed1 - ((dot1 / module1) * deltaPosition1);
                sf::Vector2f direction2 = deltaSpeed2 - ((dot2 / module2) * deltaPosition2);
                float deltaDirection1 = sqrt(pow(direction1.x, 2) + pow(direction1.y, 2));
                float deltaDirection2 = sqrt(pow(direction2.y, 2) + pow(direction2.x, 2));
                sf::Vector2f normalizeDirection1 = {direction1.x / deltaDirection1, direction1.y / deltaDirection1};
                sf::Vector2f normalizeDirection2 = {direction2.x / deltaDirection2, direction2.y / deltaDirection2};
                speed[fi].x = speed[fi].x * normalizeDirection1.x;
                speed[fi].y = speed[fi].y * normalizeDirection1.y;
                speed[si].y = speed[si].y * normalizeDirection2.y;
                speed[si].x = speed[si].x * normalizeDirection2.x;
            }
        }
    }
}

float speedInit(std::vector<sf::Vector2f> &speed)
{
    for (int i = 0; i < QUANTITY_OF_BALLS; i++)
    {
        speed.push_back({150, 150});
    }
}

void setPositions(std::vector<sf::CircleShape> &balls, float deltaTime, std::vector<sf::Vector2f> &speed)
{
    for (int i = 0; i < QUANTITY_OF_BALLS; i++)
    {
        sf::Vector2f position = balls[i].getPosition();
        if (((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed[i].x > 0)) || (position.x < 0))
        {
            speed[i].x = -speed[i].x;
        }
        if (((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed[i].y > 0)) || (position.y < 0))
        {
            speed[i].y = -speed[i].y;
        }
        const float x = position.x + speed[i].x * deltaTime;
        const float y = position.y + speed[i].y * deltaTime;
        const sf::Vector2f newPosition = {x, y};

        balls[i].setPosition(newPosition);
    }
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<sf::CircleShape> &balls)
{
    window.clear();
    for (int i = 0; i < QUANTITY_OF_BALLS; i++)
    {
        window.draw(balls[i]);
    }
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Balls balls balls");
    const sf::Vector2f position = {10, 350};
    std::vector<sf::Color> colors;
    std::vector< sf::Vector2f> speed;
    std::vector<sf::CircleShape> balls;
    speedInit(speed);
    initColors(colors);
    initBalls(balls, colors);
    sf::Clock deltaClock;

    while (window.isOpen())
    {
        const float deltaTime = deltaClock.restart().asSeconds();
        pollEvents(window);
        setPositions(balls, deltaTime, speed);
        repulsionHandler(balls, speed);
        redrawFrame(window, balls);
    }
    return 0;
}
