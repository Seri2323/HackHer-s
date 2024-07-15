#pragma once
#include "../defines.h"
#include "../utilities/justForgeAnimator.h"
#include <SFML/System/Vector2.hpp>
#include <vector>



class Dash
{
public:
    Dash(sf::RenderWindow* WINDOW);
    bool run();

    // - - -
    sf::Color backgroundColor = sf::Color::White;
    sf::RenderWindow* window;
    unsigned int windowWidth = WIDTH;
    unsigned int windowHeight = HEIGHT;

    // - - -
    std::string textureDir = TEXTURE_DIR;
    std::string fontDir = FONT_DIR;
    std::string soundDir = SOUND_DIR;

    // - - -
    unsigned char cardCount = 3;
    std::string cardTextureFiles[3] = {"card1.png", "card2.png", "card3.png"};
    sf::Texture cardTextures[3];
    sf::Sprite cards[3];
    bool animatingCard[3] = {false, false, false};
    std::vector<sf::Vector2f> scale = {sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0)};

    justForgeAnimator animator;

private:
    bool update();
    void render();
};
