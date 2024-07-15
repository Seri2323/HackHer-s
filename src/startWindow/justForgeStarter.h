#pragma once
#include "../defines.h"
#include <SFML/Graphics/RenderWindow.hpp>

// - - -  - - -  - - -


class StartScreen
{
public:
    StartScreen(sf::RenderWindow* WINDOW);
    StartScreen(sf::RenderWindow* WINDOW, unsigned int WINDOW_WIDTH, unsigned int WINDOW_HEIGHT, std::string TEXTURE_DIRECTORY, std::string FONT_DIRECTORY, std::string SOUND_DIRECTORY);
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
    std::string logoTextureFile = LOGO_TEXTURE_FILE;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::Font logoFont;
    sf::Text logoText;


private:
    void update();
    void render();
};
