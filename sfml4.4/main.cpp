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

void onMousePressed(sf::Vector2f &mousePosition, sf::RenderWindow &window)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    mousePosition = window.mapPixelToCoords(pixelPos);
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
        case sf::Event::MouseButtonPressed:
        onMousePressed(mousePosition, window);
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

void setDirection(sf::Sprite &cat, const sf::Vector2f &mousePosition)
{
    if(!(cat.getPosition().x - 1 < mousePosition.x && cat.getPosition().x + 1 >  mousePosition.x))
    if(mousePosition.x > cat.getPosition().x)
    {
        cat.setOrigin({0, 0});
        cat.setScale(1, 1);
    }
    else
    {
        cat.setOrigin({40, 0});
        cat.setScale(-1, 1);
    }    
}
    

void update(const sf::Vector2f &mousePosition, sf::Sprite &cat, sf::Sprite &point, float deltaTime, sf::RenderWindow &window)
{
    sf::Vector2f motion = mousePosition - cat.getPosition();
    sf::Vector2f direction;
    direction.x = motion.x / sqrt(pow(motion.x, 2) + pow(motion.y, 2));
    direction.y = motion.y / sqrt(pow(motion.x, 2) + pow(motion.y, 2));
    float speed = MAX_SPEED * deltaTime;
    sf::Vector2f position = cat.getPosition() + direction * speed;

    point.setPosition(mousePosition);
    setDirection(cat, mousePosition);
    cat.setPosition(position);
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &point)
{
    window.clear();
    window.draw(cat);
    window.draw(point);
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

    sf::Texture catTexture;
    sf::Sprite catSprite;
    sf::Vector2f mousePosition;
    sf::Texture pointTexture;
    sf::Sprite pointSprite;
   
    if (!catTexture.loadFromFile("images/cat.png") || !pointTexture.loadFromFile("images/red_pointer.png"))
    {
        return EXIT_FAILURE;
    }
    else
    {
        catSprite.setTexture(catTexture);
        catSprite.setPosition(sf::Vector2f(400, 300)); 
        pointSprite.setTexture(pointTexture);
        pointSprite.setPosition(sf::Vector2f(100, 100)); 
    }
    
    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, catSprite, pointSprite, deltaTime, window);
        redrawFrame(window, catSprite, pointSprite);
    }
}