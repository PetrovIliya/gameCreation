#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;
    sf::Clock deltaClock;
    const sf::Vector2f position = {10, 350};
    float speedX = 100.f;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

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
        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float deltaTime = deltaClock.restart().asSeconds();
        const float time = clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float x = x + speedX * deltaTime;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        std::cout << wavePhase << std::endl;
        const sf::Vector2f offset = {x, y};

        if((((position.x + offset.x) + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0)) ||  (position.x + offset.x < 0))
        {
            speedX = -speedX;
        }       
        ball.setPosition(position + offset);

        window.clear();
        window.draw(ball);
        window.display();
    }
    return 0;
}
