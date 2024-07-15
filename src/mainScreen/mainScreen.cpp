#include "mainScreen.h"
#include "../utilities/justForgeMouse.h"
#include <iostream>
#include <string>
#include <vector>

MainScreen::MainScreen(sf::RenderWindow* WINDOW) : animator([this]() { render(); }), dataCardEngine(CLOTH_DATA_TEXTURE_DIR)
{
    window = WINDOW;
    window->display();

    if (!logoTexture.loadFromFile(textureDir + logoTextureFile))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load texture: " + textureDir + logoTextureFile);
    }

    logoTexture.setSmooth(true);
    logo.setTexture(logoTexture);
    logo.setOrigin(logo.getGlobalBounds().width / 2, logo.getGlobalBounds().height / 2);
    //logo texture in top left corner
    logo.setPosition(logo.getGlobalBounds().width / 2, logo.getGlobalBounds().height / 2);
    logo.setScale(1.2, 1.2);
    logo.move(16, 16); // padding


    // - - - 
    // Profile wardrobe and shopping bag buttons are top right corner in horizontal stack
    
    // shopping bag button
    if (!shoppingBagTexture.loadFromFile(textureDir + shoppingBagTextureFile))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load texture: " + textureDir + shoppingBagTextureFile);
    }
    shoppingBagTexture.setSmooth(true);
    shoppingBag.setTexture(shoppingBagTexture);
    shoppingBag.setOrigin(shoppingBag.getGlobalBounds().width / 2, shoppingBag.getGlobalBounds().height / 2);
    shoppingBag.setScale(0.6, 0.6);
    shoppingBag.setPosition(window->getSize().x - shoppingBag.getGlobalBounds().width / 2, shoppingBag.getGlobalBounds().height / 2);
    shoppingBag.move(-16, 16);

    // wardrobe button
    if (!wardrobeTexture.loadFromFile(textureDir + wardrobeTextureFile))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load texture: " + textureDir + wardrobeTextureFile);
    }
    wardrobeTexture.setSmooth(true);
    wardrobe.setTexture(wardrobeTexture);
    wardrobe.setOrigin(wardrobe.getGlobalBounds().width / 2, wardrobe.getGlobalBounds().height / 2);
    wardrobe.setScale(0.6, 0.6);
    wardrobe.setPosition(window->getSize().x - wardrobe.getGlobalBounds().width / 2 - shoppingBag.getGlobalBounds().width, wardrobe.getGlobalBounds().height / 2);
    wardrobe.move(-16, 16);

    // profile button
    if (!profileTexture.loadFromFile(textureDir + profileTextureFile))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load texture: " + textureDir + profileTextureFile);
    }
    profileTexture.setSmooth(true);
    profile.setTexture(profileTexture);
    profile.setOrigin(profile.getGlobalBounds().width / 2, profile.getGlobalBounds().height / 2);
    profile.setScale(0.6, 0.6);
    profile.setPosition(window->getSize().x - profile.getGlobalBounds().width / 2 - wardrobe.getGlobalBounds().width - shoppingBag.getGlobalBounds().width, profile.getGlobalBounds().height / 2);
    profile.move(-16, 16);

    // - - -
    // 3 buttons: dislike, add to wardrobe, like
    for (int i = 0; i < 3; ++i)
    {
        if (!buttonTextures[i].loadFromFile(textureDir + buttonTextureFiles[i]))
        {
            throw std::system_error(errno, std::system_category(), "Failed to load texture: " + textureDir + buttonTextureFiles[i]);
        }
        buttonTextures[i].setSmooth(true);
        buttons[i].setTexture(buttonTextures[i]);
        buttons[i].setOrigin(buttons[i].getGlobalBounds().width / 2, buttons[i].getGlobalBounds().height / 2);
        //buttons are in a horizontal stack at the bottom of the screen
        buttons[i].setPosition((i + 1) * window->getSize().x / 4, window->getSize().y - 128);
    }

    // - - -
    // Load fonts
    if (!nameFont.loadFromFile(FONT_DIR + NameFont))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load font: " + NameFont);
    }
    if (!bioFont.loadFromFile(FONT_DIR + BioFont))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load font: " + BioFont);
    }


    // generate the first two cards
    generateCard();
    generateCard();
}

void MainScreen::run()
{
    window->clear(backgroundColor);
    justForgeAnimator animator([this]() { render(); });

    while (window->isOpen())
    {
        update();
        render();
    }
}

void MainScreen::render()
{
    window->clear(backgroundColor);
    window->draw(logo);
    window->draw(profile);
    window->draw(wardrobe);
    window->draw(shoppingBag);
    for (int i = 0; i < 3; ++i)
    {
        window->draw(buttons[i]);
    }
    //display the current two cards with the current card on top
    window->draw(cardData[currentCard].rectangle);
    window->draw(cardData[currentCard].name);
    window->draw(cardData[currentCard].bio);

    //window->draw(cardData[(currentCard + 1) % 2].rectangle);
    //window->draw(cardData[(currentCard + 1) % 2].name);
    //window->draw(cardData[(currentCard + 1) % 2].bio);

    window->display();
}


void MainScreen::update()
{
    std::vector<sf::Transformable> targets;
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                }
                break;

            case sf::Event::MouseMoved:
                //check for all buttons if mouse is over them
                for (int i = 0; i < 3; ++i)
                {
                    if (justForgeMouse::isMouseInRect(window, buttons[i].getPosition(), sf::Vector2f(buttons[i].getGlobalBounds().width, buttons[i].getGlobalBounds().height)))
                    {
                        if (!animatingButtons[i])
                        {
                            animator.scale(buttons[i], sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.1, 1.1), 0.1f);
                            animatingButtons[i] = true;
                        }
                    }
                    else
                    {
                        if (animatingButtons[i])
                        {
                            animator.scale(buttons[i], sf::Vector2f(1.1, 1.1), sf::Vector2f(1.0f, 1.0f), 0.1f);
                            animatingButtons[i] = false;
                        }
                    }
                }

                //check for profile, wardrobe, shopping bag buttons
                if (justForgeMouse::isMouseInRect(window, profile.getPosition(), sf::Vector2f(profile.getGlobalBounds().width, profile.getGlobalBounds().height)))
                {
                    if (!animatingProfile)
                    {
                        animator.scale(profile, sf::Vector2f(0.6, 0.6), sf::Vector2f(0.7, 0.7), 0.1f);
                        animatingProfile = true;
                    }
                }
                else
                {
                    if (animatingProfile)
                    {
                        animator.scale(profile, sf::Vector2f(0.7, 0.7), sf::Vector2f(0.6, 0.6), 0.1f);
                        animatingProfile = false;
                    }
                }

                if (justForgeMouse::isMouseInRect(window, wardrobe.getPosition(), sf::Vector2f(wardrobe.getGlobalBounds().width, wardrobe.getGlobalBounds().height)))
                {
                    if (!animatingWardrobe)
                    {
                        animator.scale(wardrobe, sf::Vector2f(0.6, 0.6), sf::Vector2f(0.7, 0.7), 0.1f);
                        animatingWardrobe = true;
                    }
                }
                else
                {
                    if (animatingWardrobe)
                    {
                        animator.scale(wardrobe, sf::Vector2f(0.7, 0.7), sf::Vector2f(0.6, 0.6), 0.1f);
                        animatingWardrobe = false;
                    }
                }
                
                if (justForgeMouse::isMouseInRect(window, shoppingBag.getPosition(), sf::Vector2f(shoppingBag.getGlobalBounds().width, shoppingBag.getGlobalBounds().height)))
                {
                    if (!animatingShoppingBag)
                    {
                        animator.scale(shoppingBag, sf::Vector2f(0.6, 0.6), sf::Vector2f(0.7, 0.7), 0.1f);
                        animatingShoppingBag = true;
                    }
                }
                else
                {
                    if (animatingShoppingBag)
                    {
                        animator.scale(shoppingBag, sf::Vector2f(0.7, 0.7), sf::Vector2f(0.6, 0.6), 0.1f);
                        animatingShoppingBag = false;
                    }
                }

                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePosition = justForgeMouse::getMousePosition(window);

                    // check if the mouse is clicking on any of the buttons
                    for (int i = 0; i < 3; ++i)
                    {
                        if (justForgeMouse::isPointInRect(mousePosition, buttons[i].getPosition(), sf::Vector2f(buttons[i].getGlobalBounds().width, buttons[i].getGlobalBounds().height)))
                        {
                            switch (i)
                            {
                                case 1:
                                    animatingCard[currentCard] = true;

                                    break;

                                case 0:
                                    animator.slideGhost(cardData[currentCard].rectangle, cardData[currentCard].rectangle.getPosition(), sf::Vector2f(-1000.0f, cardData[currentCard].rectangle.getPosition().y), 0.2f);
                                    animator.slideGhost(cardData[currentCard].name, cardData[currentCard].name.getPosition(), sf::Vector2f(-1000.0f, cardData[currentCard].name.getPosition().y), 0.2f);
                                    animator.slideGhost(cardData[currentCard].bio, cardData[currentCard].bio.getPosition(), sf::Vector2f(-1000.0f, cardData[currentCard].bio.getPosition().y), 0.2f);
                                    currentCard = (currentCard + 1) % 2;
                                    generateCard();
                                    break;

                                case 2:
                                    animator.slideGhost(cardData[currentCard].rectangle, cardData[currentCard].rectangle.getPosition(), sf::Vector2f(1000.0f, cardData[currentCard].rectangle.getPosition().y), 0.2f);
                                    animator.slideGhost(cardData[currentCard].name, cardData[currentCard].name.getPosition(), sf::Vector2f(1000.0f, cardData[currentCard].name.getPosition().y), 0.2f);
                                    animator.slideGhost(cardData[currentCard].bio, cardData[currentCard].bio.getPosition(), sf::Vector2f(1000.0f, cardData[currentCard].bio.getPosition().y), 0.2f);
                                    currentCard = (currentCard + 1) % 2;
                                    generateCard();
                                    // like
                                    break;

                                default:
                                    break;
                            }
                        }
                    }

                    // check if the mouse is clicking on any of the profile, wardrobe, shopping bag buttons
                    if (justForgeMouse::isPointInRect(mousePosition, profile.getPosition(), sf::Vector2f(profile.getGlobalBounds().width, profile.getGlobalBounds().height)))
                    {
                        // profile button clicked
                    }

                    if (justForgeMouse::isPointInRect(mousePosition, wardrobe.getPosition(), sf::Vector2f(wardrobe.getGlobalBounds().width, wardrobe.getGlobalBounds().height)))
                    {
                        // wardrobe button clicked
                    }

                    if (justForgeMouse::isPointInRect(mousePosition, shoppingBag.getPosition(), sf::Vector2f(shoppingBag.getGlobalBounds().width, shoppingBag.getGlobalBounds().height)))
                    {
                        // shopping bag button clicked
                    }
                }
                break;

            default:
                break;
        }
    }
}


void MainScreen::generateCard()
{
    std::vector<std::string> card = dataCardEngine.generateDataCard();
    if (card.empty())
    {
        std::cerr << "Failed to generate card" << std::endl;
        return;
    }

    cardData[currentCard].textureFile = CLOTH_DATA_TEXTURE_DIR + card[2];
    cardData[currentCard].nameText = card[1];
    cardData[currentCard].bioText = card[0];

    //load the textures
    if (!cardData[currentCard].texture.loadFromFile(cardData[currentCard].textureFile))
    {
        throw std::system_error(errno, std::system_category(), "Failed to load texture: " + cardData[currentCard].textureFile);
    }
    cardData[currentCard].texture.setSmooth(true);
    cardData[currentCard].rectangle.setTexture(&cardData[currentCard].texture);
    cardData[currentCard].rectangle.setSize(cardSize);
    cardData[currentCard].rectangle.setOrigin(cardData[currentCard].rectangle.getGlobalBounds().width / 2, cardData[currentCard].rectangle.getGlobalBounds().height / 2);
    // position in center in x and below the logo with a padding of 32
    animator.slide(cardData[currentCard].rectangle, sf::Vector2f(-1000.0f, logo.getGlobalBounds().height + cardSize.y / 2 + 32), sf::Vector2f(window->getSize().x / 2, logo.getGlobalBounds().height + cardSize.y / 2 + 32), 0.2f);
    cardData[currentCard].rectangle.setPosition(window->getSize().x / 2, logo.getGlobalBounds().height + cardSize.y / 2 + 32);


    cardData[currentCard].name.setFont(nameFont);
    cardData[currentCard].name.setString(cardData[currentCard].nameText);
    cardData[currentCard].name.setCharacterSize(20);
    cardData[currentCard].name.setFillColor(sf::Color::Black);
    //position below the image, to the left with a padding of 32 in x and 16 in y
    animator.slide(cardData[currentCard].name, sf::Vector2f(-1000, cardData[currentCard].rectangle.getPosition().y + cardSize.y / 2 + 16), sf::Vector2f(32, cardData[currentCard].rectangle.getPosition().y + cardSize.y / 2 + 16), 0.2f);
    cardData[currentCard].name.setPosition(32, cardData[currentCard].rectangle.getPosition().y + cardSize.y / 2 + 16);


    cardData[currentCard].bio.setFont(bioFont);
    cardData[currentCard].bio.setString(cardData[currentCard].bioText);
    cardData[currentCard].bio.setCharacterSize(16);
    cardData[currentCard].bio.setFillColor(sf::Color::Black);
    cardData[currentCard].bio.setOrigin(cardData[currentCard].bio.getGlobalBounds().width / 2, cardData[currentCard].bio.getGlobalBounds().height / 2);
    //position below the name, to the center aove the add to card button with a padding of 64 in y
    animator.slide(cardData[currentCard].bio, sf::Vector2f(-1000, cardData[currentCard].name.getPosition().y + 64), sf::Vector2f(window->getSize().x / 2, cardData[currentCard].name.getPosition().y + 64), 0.2f);
    cardData[currentCard].bio.setPosition(window->getSize().x / 2, buttons[1].getPosition().y - 64);

} 
