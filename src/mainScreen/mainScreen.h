#pragma once
#include "../defines.h"
#include "../utilities/justForgeAnimator.h"
#include "../dataCard/dataCard.h"


typedef struct cardData
{
    sf::Texture texture;
    sf::RectangleShape rectangle;
    sf::Text name;
    sf::Text bio;

    std::string textureFile;
    std::string nameText;
    std::string bioText;
} cardData;

class MainScreen
{
public:
  MainScreen(const MainScreen &) = default;
  MainScreen(MainScreen &&) = default;
  MainScreen &operator=(const MainScreen &) = default;
  MainScreen &operator=(MainScreen &&) = default;
  MainScreen(sf::RenderWindow *WINDOW);
  void run();

private:
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
    /*
     * Myntra logo, profile button, wardrobe button, shopping bag button
     * One image in the center
     * 3 texts: one for brand, one for name, one for description
     * 3 buttons: one to add to wardrobe, one to scroll right, one to scroll left
    */

    // - - -
    std::string logoTextureFile = "smallLogo.png";
    sf::Texture logoTexture;
    sf::Sprite logo;

    std::string profileTextureFile = "profileTexture.png";
    sf::Texture profileTexture;
    sf::Sprite profile;
    bool animatingProfile = false;

    std::string wardrobeTextureFile = "wardrobeTexture.png";
    sf::Texture wardrobeTexture;
    sf::Sprite wardrobe;
    bool animatingWardrobe = false;

    std::string shoppingBagTextureFile = "shoppingBagTexture.png";
    sf::Texture shoppingBagTexture;
    sf::Sprite shoppingBag;
    bool animatingShoppingBag = false;

    std::string buttonTextureFiles[3] = {"dislike.png", "addWardrobe.png", "like.png"};
    sf::Texture buttonTextures[3];
    sf::Sprite buttons[3];
    bool animatingButtons[3] = {false, false, false};

    DataCard dataCardEngine; // for double buffering
    std::vector<std::string> dataCard;

    // - - -
    /*
     We will have everything double
     Double image, double description, double name 
     so that if image generation takes time, we can show the previous image
    */
    justForgeAnimator animator;

    void update();
    void render();
    
    cardData cardData[2];
    bool animatingCard[2] = {false, false};
    unsigned char currentCard = 0;
    void generateCard();

    std::string NameFont = "JetBrainsMono-ExtraBold.ttf";
    std::string BioFont = "JetBrainsMono-LightItalic.ttf";

    sf::Font nameFont;
    sf::Font bioFont;

    sf::Vector2f cardSize = sf::Vector2f(WIDTH - 32, HEIGHT / 2);

    //response image
    std::string responseTextureFile[3] = {"likeResponse.png", "dislikeResponse.png", "wardrobeResponse.png"};
    sf::Texture responseTexture;
    sf::Sprite response;

    bool showResponse = false;
    
};
