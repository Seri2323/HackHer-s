#include "justForgeAnimator.h"
#include <SFML/Graphics/Sprite.hpp>

justForgeAnimator::justForgeAnimator(std::function<void()> RENDER_FUNCTION)
{
    renderFunction = RENDER_FUNCTION;
}

void justForgeAnimator::slide(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION)
{
    aClock.restart();
    float elapsedTime = 0.0f;
    float totalDuration = DURATION;

    while (elapsedTime < totalDuration)
    {
        elapsedTime = aClock.getElapsedTime().asSeconds();
        float progress = std::min(1.0f, elapsedTime / totalDuration);

        sf::Vector2f interpolatedPosition = START + (END - START) * progress;
        TARGET.setPosition(interpolatedPosition);

        renderFunction();
        if (progress >= 1.0f)
        { 
            break;
        }
    }

    TARGET.setPosition(END);
}

void justForgeAnimator::scale(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION)
{
    aClock.restart();
    float elapsedTime = 0.0f;
    float totalDuration = DURATION;

    while (elapsedTime < totalDuration)
    {
        elapsedTime = aClock.getElapsedTime().asSeconds();
        float progress = std::min(1.0f, elapsedTime / totalDuration);

        sf::Vector2f interpolatedScale = START + (END - START) * progress;
        TARGET.setScale(interpolatedScale);

        renderFunction();
        if (progress >= 1.0f)
        {
            break;
        }
    }

    TARGET.setScale(END);
}

void justForgeAnimator::slideGhost(sf::Sprite& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION)
{
    //basically slide but with increasing opacity
    aClock.restart();
    float elapsedTime = 0.0f;
    float totalDuration = DURATION;

    while (elapsedTime < totalDuration)
    {
        elapsedTime = aClock.getElapsedTime().asSeconds();
        float progress = std::min(1.0f, elapsedTime / totalDuration);

        sf::Vector2f interpolatedPosition = START + (END - START) * progress;
        TARGET.setPosition(interpolatedPosition);

        sf::Color interpolatedColor = TARGET.getColor();
        interpolatedColor.a = 255 * progress;
        TARGET.setColor(interpolatedColor);

        renderFunction();
        if (progress >= 1.0f)
        {
            break;
        }
    }
}

void justForgeAnimator::slideGhost(sf::Shape& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION)
{
    //basically slide but with increasing opacity
    aClock.restart();
    float elapsedTime = 0.0f;
    float totalDuration = DURATION;

    while (elapsedTime < totalDuration)
    {
        elapsedTime = aClock.getElapsedTime().asSeconds();
        float progress = std::min(1.0f, elapsedTime / totalDuration);

        sf::Vector2f interpolatedPosition = START + (END - START) * progress;
        TARGET.setPosition(interpolatedPosition);

        sf::Color interpolatedColor = TARGET.getFillColor();
        interpolatedColor.a = 255 * progress;
        TARGET.setFillColor(interpolatedColor);

        renderFunction();
        if (progress >= 1.0f)
        {
            break;
        }
    }
}

void justForgeAnimator::slideGhost(sf::Text& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION)
{
    //basically slide but with increasing opacity
    aClock.restart();
    float elapsedTime = 0.0f;
    float totalDuration = DURATION;

    while (elapsedTime < totalDuration)
    {
        elapsedTime = aClock.getElapsedTime().asSeconds();
        float progress = std::min(1.0f, elapsedTime / totalDuration);

        sf::Vector2f interpolatedPosition = START + (END - START) * progress;
        TARGET.setPosition(interpolatedPosition);

        sf::Color interpolatedColor = TARGET.getFillColor();
        interpolatedColor.a = 255 * progress;
        TARGET.setFillColor(interpolatedColor);

        renderFunction();
        if (progress >= 1.0f)
        {
            break;
        }
    }
}


void justForgeAnimator::rotateFall(std::vector<sf::Transformable>& TARGETS, float DURATION, bool ROTATE_RIGHT)
{
    //rotate the targets and make them fall in y until they are out of screen
    aClock.restart();
    float elapsedTime = 0.0f;
    float totalDuration = DURATION;

    while (elapsedTime < totalDuration)
    {
        elapsedTime = aClock.getElapsedTime().asSeconds();
        float progress = std::min(1.0f, elapsedTime / totalDuration);

        for (auto& target : TARGETS)
        {
            target.rotate(ROTATE_RIGHT ? 1.0f : -1.0f);
            target.move(0, 10);
        }

        renderFunction();
        if (progress >= 1.0f)
        {
            break;
        }
    }
    for (auto& target : TARGETS)
    {
        target.setPosition(-1000, -1000);
    }
}
