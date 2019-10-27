#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#define BALL_SIZE 50
#define QUANTITY_OF_BALLS 5


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

void check(std::vector<sf::CircleShape> &balls, std::vector<sf::Vector2f> &speed)
{
    constexpr size_t SIZE = QUANTITY_OF_BALLS;
    for (size_t fi = 0; fi < SIZE; ++fi)
    {
        for (size_t si = fi + 1; si < SIZE; ++si)
        {
            sf::Vector2f position1 = balls[si].getPosition();
            sf::Vector2f position2 = balls[fi].getPosition();
            sf::Vector2f deltaPosition = position2 - position1;
            
            if(deltaPosition.x < 0)
            {
                deltaPosition.x = -deltaPosition.x;
            }
            if(deltaPosition.y < 0)
            {
                deltaPosition.y = -deltaPosition.y;
            }
            if (deltaPosition.x <= 2 * BALL_SIZE && deltaPosition.y <= 2 * BALL_SIZE)
            {
                speed[fi].x = -speed[fi].x;
                speed[fi].y = -speed[fi].y;
                speed[si].x = -speed[si].x;
                speed[si].y = -speed[si].y;
                std::cout <<deltaPosition.x << std::endl;
            }
        }
    }
}

float speedInit(std::vector<sf::Vector2f> &speed)
{
    for (int i = 0; i < QUANTITY_OF_BALLS; i++)
    {
        speed.push_back({100, 100});
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        const float deltaTime = deltaClock.restart().asSeconds();

        check(balls, speed);
        setPositions(balls, deltaTime, speed);
        
        window.clear();
        for (int i = 0; i < QUANTITY_OF_BALLS; i++)
        {
            window.draw(balls[i]);
        }
        window.display();
    }
    return 0;
}