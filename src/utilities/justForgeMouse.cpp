#include "justForgeMouse.h"

justForgeMouse::justForgeMouse()
{
}

bool justForgeMouse::isPointInRect(sf::Vector2f POINT, sf::Vector2f CENTER, sf::Vector2f SIZE)
{
    return (POINT.x > CENTER.x - SIZE.x / 2 && POINT.x < CENTER.x + SIZE.x / 2 && POINT.y > CENTER.y - SIZE.y / 2 && POINT.y < CENTER.y + SIZE.y / 2);
}

bool justForgeMouse::isPointInCircle(sf::Vector2f POINT, sf::Vector2f CENTER, float RADIUS)
{
    return (POINT.x - CENTER.x) * (POINT.x - CENTER.x) + (POINT.y - CENTER.y) * (POINT.y - CENTER.y) < RADIUS * RADIUS;
}

bool justForgeMouse::isMouseInRect(sf::RenderWindow* WINDOW, sf::Vector2f CENTER, sf::Vector2f SIZE)
{
    return isPointInRect(getMousePosition(WINDOW), CENTER, SIZE);
}

bool justForgeMouse::isMouseInCircle(sf::RenderWindow* WINDOW, sf::Vector2f CENTER, float RADIUS)
{
    return isPointInCircle(getMousePosition(WINDOW), CENTER, RADIUS);
}

sf::Vector2f justForgeMouse::getMousePosition(sf::RenderWindow* WINDOW)
{
    return sf::Vector2f(sf::Mouse::getPosition(*WINDOW).x, sf::Mouse::getPosition(*WINDOW).y);
}
