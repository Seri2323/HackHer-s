#include "dash.h"
#include "../utilities/justForgeAnimator.h"
#include "../utilities/justForgeMouse.h"

#include <climits>
#include <system_error>

Dash::Dash(sf::RenderWindow* WINDOW) : animator([this]() { render(); })
{
    window = WINDOW;
    window->display();

    sf::Vector2f cardSize(450, 186);

    for (int i = 0; i < cardCount; ++i)
    {
        if (!cardTextures[i].loadFromFile(textureDir + cardTextureFiles[i]))
        {
            throw std::system_error(errno, std::system_category(), "Failed to load texture: " + textureDir + cardTextureFiles[i]);
        }
        cardTextures[i].setSmooth(true);
        cards[i].setTexture(cardTextures[i]);
        cards[i].setOrigin(cards[i].getGlobalBounds().width / 2, cards[i].getGlobalBounds().height / 2);

        //stack the cards on top of each other with a padding of 64
        cards[i].setPosition(window->getSize().x / 2, window->getSize().y / 2 + 224 * i);
        cards[i].setColor(sf::Color(255, 255, 255, 0));
        scale[i] = sf::Vector2f(cardSize.x / cards[i].getGlobalBounds().width, cardSize.y / cards[i].getGlobalBounds().height);
        cards[i].setScale(scale[i]);
    }
}

bool Dash::run()
{
    window->clear(backgroundColor);
    justForgeAnimator animator([this]() { render(); });

    for (int i = 0; i < cardCount; ++i)
    {
        int x = cards[i].getPosition().x;
        int y = cards[i].getPosition().y - 256;
        animator.slideGhost(cards[i], sf::Vector2f(x, y + 256), sf::Vector2f(x, y), 0.25f);
    }

    while (update())
    {
        render();
    }

    return false;
}

void Dash::render()
{
    window->clear(backgroundColor);
    for (int i = 0; i < cardCount; ++i)
    {
        window->draw(cards[i]);
    }
    window->display();
}


bool Dash::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
            default:
                break;

            case sf::Event::Closed:
                window->close();
                return false;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePosition = justForgeMouse::getMousePosition(window);

                    // check if the mouse is clicking card3
                    if (justForgeMouse::isPointInRect(mousePosition, cards[2].getPosition(), sf::Vector2f(cards[2].getGlobalBounds().width, cards[2].getGlobalBounds().height)))
                    {
                        return false;
                    }
                }
                break;

            case sf::Event::MouseMoved:
                // if hovering over any card, scale it up to 1.1
                for (int i = 0; i < cardCount; ++i)
                {
                    if (justForgeMouse::isPointInRect(justForgeMouse::getMousePosition(window), cards[i].getPosition(), sf::Vector2f(cards[i].getGlobalBounds().width, cards[i].getGlobalBounds().height)))
                    {
                        switch (animatingCard[i])
                        {
                            case false:
                                animator.scale(cards[i], scale[i], scale[i] * 1.05f, 0.1f);
                                //scale card to 1.1 times the current size

                                animatingCard[i] = true;
                                break;

                            default:
                                break;
                        }     
                    }
                    else
                    {
                        switch (animatingCard[i])
                        {
                            case true:
                                animator.scale(cards[i], scale[i] * 1.05f, scale[i], 0.1f);
                                animatingCard[i] = false;
                                break;

                            default:
                                break;
                        }
                    }
                }
        }
    }
    return true;
}
