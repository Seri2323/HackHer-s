#pragma once
#include "../defines.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <functional>

class justForgeAnimator
{
public:
    justForgeAnimator(std::function<void()> RENDER_FUNCTION);

    void slide(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);
    
    void scale(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);

    void slideGhost(sf::Sprite& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);
    
    void slideGhost(sf::Shape& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);

    void slideGhost(sf::Text& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);

    void rotateFall(std::vector<sf::Transformable>& TARGETS, float DURATION, bool ROTATE_RIGHT = true);

    enum class animationType
    {
        SLIDE,
        SCALE,
        SLIDE_GHOST
    };
   
    void animate(sf::Transformable& TARGET, std::vector<animationType>& ANIMATIONS, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);

private:
    sf::Clock aClock;
    std::function<void()> renderFunction;
};
