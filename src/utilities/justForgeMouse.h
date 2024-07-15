#pragma once
#include "../defines.h"

class justForgeMouse
{
public:
    justForgeMouse();

    static bool isPointInRect(sf::Vector2f POINT, sf::Vector2f CENTER, sf::Vector2f SIZE);
    static bool isPointInCircle(sf::Vector2f POINT, sf::Vector2f CENTER, float RADIUS);

    static bool isMouseInRect(sf::RenderWindow* WINDOW, sf::Vector2f CENTER, sf::Vector2f SIZE);
    static bool isMouseInCircle(sf::RenderWindow* WINDOW, sf::Vector2f CENTER, float RADIUS);

    static sf::Vector2f getMousePosition(sf::RenderWindow* WINDOW);
};
