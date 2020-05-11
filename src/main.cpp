#include "main.h"

#include <iostream>

int windowWidth = 960;
int windowHeight = 540;

void initializeResources(Resources &res)
{
    if (!res.backgroundTexture.loadFromFile("assets/grass-FWStudio-Pexel.jpg"))
    {
        std::cerr << "Cannot load background" << std::endl;
    }
    res.backgroundTexture.setRepeated(true);
    res.backgroundSprite.setTexture(res.backgroundTexture);
    res.backgroundSprite.setTextureRect(sf::IntRect(0, 0, windowWidth, windowHeight));

    if (!res.playerTexture.loadFromFile("assets/MrBlock.png"))
    {
        std::cerr << "Cannot load player" << std::endl;
    }
    res.playerSprite.setTexture(res.playerTexture);
    float playerScale = 60.f / res.playerTexture.getSize().y;
    res.playerSprite.setScale(playerScale, playerScale);
    res.playerSprite.setPosition((windowWidth - res.playerTexture.getSize().x * playerScale) / 2,
                                 (windowHeight - res.playerTexture.getSize().y * playerScale) / 2);
}

void drawScreen(sf::RenderWindow &window, Resources &res)
{
    window.draw(res.backgroundSprite);
    window.draw(res.playerSprite);
}

void handleInput(sf::Event event, Resources &res)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
    if(event.key.code == sf::Keyboard::Up)
        {
            sf::IntRect rect = res.backgroundSprite.getTextureRect();
            rect.top -= 10;
            res.backgroundSprite.setTextureRect(rect);
        }
        else if(event.key.code == sf::Keyboard::Down)
        {
            sf::IntRect rect = res.backgroundSprite.getTextureRect();
            rect.top += 10;
            res.backgroundSprite.setTextureRect(rect);
        }
        else if(event.key.code == sf::Keyboard::Left)
        {
            sf::IntRect rect = res.backgroundSprite.getTextureRect();
            rect.left -= 10;
            res.backgroundSprite.setTextureRect(rect);
        }
        else if(event.key.code == sf::Keyboard::Right)
        {
            sf::IntRect rect = res.backgroundSprite.getTextureRect();
            rect.left += 10;
            res.backgroundSprite.setTextureRect(rect);
        }
        break;
    }
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Blockman is awesome!");
    window.setFramerateLimit(60);

    Resources res = {};
    initializeResources(res);

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();

            handleInput(event, res);
        }

        // Clear screen
        window.clear();

        // Update the window

        drawScreen(window, res);
        window.display();
    }

    return 0;
}
