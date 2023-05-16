#pragma once

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Debug
{
sf::Font font;
sf::Text pausedLabel;
sf::Text coordsLabel;

bool menu = false;

public:
    Debug()
    {
        font.loadFromFile("../fonts/bit5x3.ttf");

        // Paused label
        sf::Text pausedLabel;
        pausedLabel.setString("Paused");
        pausedLabel.setFont(font);
        pausedLabel.setCharacterSize(textSize);
        pausedLabel.setFillColor(textColor);
        pausedLabel.setPosition(10, height - textSize - 10);

        // Coords label
        sf::Text coordsLabel;
        coordsLabel.setFont(font);
        coordsLabel.setCharacterSize(15);
        coordsLabel.setFillColor(textColor);
        coordsLabel.setPosition(10, 10);
    }

    void toggleMenu();
};