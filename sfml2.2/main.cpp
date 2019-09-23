#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

void drawPolarRose()
{
    constexpr int pointCount = 200;
    const sf::Vector2f position = {300, 350};    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 650}), "Ellips",
        sf::Style::Default, settings);
    sf::ConvexShape ellipse;
    ellipse.setPosition(position);
    ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    ellipse.setPointCount(pointCount);
    sf::Clock clock;
    
    while(window.isOpen())
    {
        for(int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float angle = float(2 * M_PI * pointNo) / float(pointCount);
            const float ellipseRadius = 200 * sin(6 * angle);
            sf::Vector2f point = sf::Vector2f
            {
                ellipseRadius * std::sin(angle),
                ellipseRadius * std::cos(angle)
            };
            ellipse.setPoint(pointNo, point);
        }

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float time = clock.getElapsedTime().asSeconds();
        float movingAngle = float(2 * M_PI) * time;
        float movingRadius = 2.f;
        const float x = x + sin(movingAngle) * movingRadius;
        const float y = y + cos(movingAngle) * movingRadius;
        const sf::Vector2f offset = {x, y};
        ellipse.setPosition(position + offset);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}

int main()
{
    drawPolarRose();
}
