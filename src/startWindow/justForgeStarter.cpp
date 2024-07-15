#include "justForgeStarter.h"
#include "../utilities/justForgeAnimator.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <climits>
#include <system_error>

StartScreen::StartScreen(sf::RenderWindow* WINDOW)
{
    window = WINDOW;
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);
    window->setActive(true);
    window->clear(backgroundColor);
    //window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    window->setPosition(sf::Vector2i(0,0));
    window->display();

    if (!logoTexture.loadFromFile(textureDir + logoTextureFile))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load texture: " + textureDir + logoTextureFile);
    }
    logoTexture.setSmooth(true);
    window->setIcon(logoTexture.getSize().x, logoTexture.getSize().y, logoTexture.copyToImage().getPixelsPtr());

    logoSprite.setTexture(logoTexture);
    logoSprite.setOrigin(logoSprite.getGlobalBounds().width / 2, logoSprite.getGlobalBounds().height / 2);
    logoSprite.setPosition(window->getSize().x / 2, window->getSize().y / 2 + 50);

    if (!logoFont.loadFromFile(fontDir + "JetBrainsMono-ExtraBold.ttf"))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load font: " + fontDir + "JetBrainsMono-ExtraBold.ttf");
    }
    logoText.setFont(logoFont);
    logoText.setString("Santra");
    logoText.setCharacterSize(36);
    logoText.setFillColor(sf::Color::Black);
    logoText.setOrigin(logoText.getGlobalBounds().width / 2, logoText.getGlobalBounds().height / 2);
    logoText.setPosition(sf::Vector2f(-INT_MAX, -INT_MAX));
    //logoText.setPosition(window.getSize().x / 2 - logoText.getGlobalBounds().width / 2, window.getSize().y / 2 + logoSprite.getGlobalBounds().height / 2 + 10);
}

bool StartScreen::run()
{
    justForgeAnimator animator([this]() { render(); });
    //slide a bit up from bottom

    int x = logoSprite.getPosition().x;
    int y = logoSprite.getPosition().y - 64;
    animator.slideGhost(logoSprite, sf::Vector2f(x, y + 32), sf::Vector2f(x, y), 1.0f);

    y = window->getSize().y - 128;
    animator.slideGhost(logoText, sf::Vector2f(x, y), sf::Vector2f(x, y), 0.5f);

    // run update and render loop for 2 seconds
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 1)
    {
        update();
        render();
    }

    return false;
}

void StartScreen::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }
}

void StartScreen::render()
{
    window->clear(backgroundColor);
    window->draw(logoSprite);
    window->draw(logoText);
    window->display();
}
