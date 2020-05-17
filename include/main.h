#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

struct Resources
{
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    sf::Font blackChancery;

    sf::Text playerPositionText;
};

struct Player
{
    float posX;
    float posY;
};
