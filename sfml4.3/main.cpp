#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Cat");

    window.clear(sf::Color(255, 255, 255));

    sf::Texture texture;
    if (!texture.loadFromFile("images/cat.png"))
    {
         std::cout << "Texture was not loaded";
    }
    else
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(400, 300)); 
        window.draw(sprite);
        window.display();
        sf::sleep(sf::seconds(10));
    }

}