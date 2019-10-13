#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Arrow");

    window.clear(sf::Color(255, 255, 255));

    sf::ConvexShape arrow;
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
    arrow.setRotation(-80);

    window.draw(arrow);
    window.display();

    sf::sleep(sf::seconds(10));
}