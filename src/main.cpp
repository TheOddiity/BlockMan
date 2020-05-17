#include "main.h"

#include <iostream>

int windowWidth = 960;
int windowHeight = 540;

void initializeResources(Resources &res)
{
    if (!res.backgroundTexture.loadFromFile("assets/grass.jpg"))
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

    if (!res.blackChancery.loadFromFile("assets/BLKCHCRY.TTF"))
    {
        std::cerr << "Cannot load font" << std::endl;
    }
    res.playerPositionText.setFont(res.blackChancery);
    res.playerPositionText.setPosition(10, windowHeight - 30);
    res.playerPositionText.setCharacterSize(20);
    res.playerPositionText.setFillColor(sf::Color::Black);
}

void handleInput(float dt, Resources &res, Player &player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.posY -= 600 * dt;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.posY += 600 * dt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.posX -= 600 * dt;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.posX += 600 * dt;
    }
}

void update(Resources &res, Player &player)
{
    res.playerPositionText.setString("X: " + std::to_string(player.posX) + " Y: " + std::to_string(player.posY));

    //Setting the background
    sf::IntRect rect = res.backgroundSprite.getTextureRect();
    rect.top = player.posY;
    rect.left = player.posX;
    res.backgroundSprite.setTextureRect(rect);
}

void drawScreen(sf::RenderWindow &window, Resources &res)
{
    window.draw(res.backgroundSprite);
    window.draw(res.playerSprite);
    window.draw(res.playerPositionText);
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Blockman is awesome!");
    window.setFramerateLimit(60);

    sf::Clock frameTime;

    Resources res = {};
    initializeResources(res);

    Player player {0, 0};

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
        }

        // Clear screen
        window.clear();

        handleInput(frameTime.restart().asSeconds(), res, player);
        update(res, player);

        // Update the window
        drawScreen(window, res);
        window.display();
    }

    return 0;
}
