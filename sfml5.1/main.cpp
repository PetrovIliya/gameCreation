#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#define BALL_SIZE 40

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

void init(std::vector<sf::CircleShape> &balls)
{
    for (int i = 0; i < 5; i++)
    {
        sf::CircleShape ball(BALL_SIZE);
        float x = std::rand() % 700 + 100;
        float y = std::rand() % 500 + 0;
        sf::Vector2f position = {x, y};
        ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
        ball.setPosition(position);
        balls.push_back(ball);
    }
}

float speedInit(std::vector<sf::Vector2f> &speed)
{
    for (int i = 0; i < 5; i++)
    {
        speed.push_back({100, 100});
    }
}

void setPositions(std::vector<sf::CircleShape> &balls, float deltaTime, std::vector<sf::Vector2f> &speed)
{
    for (int i = 0; i < 5; i++)
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

sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
const sf::Vector2f position = {10, 350};
int main()
{
    std::vector< sf::Vector2f> speed;
    speedInit(speed);
    std::vector<sf::CircleShape> balls;
    init(balls);
    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        const float deltaTime = deltaClock.restart().asSeconds();
        setPositions(balls, deltaTime, speed);
        window.clear();
        for (int i = 0; i < 5; i++)
        {
            window.draw(balls[i]);
        }
        window.display();
    }
    return 0;
}