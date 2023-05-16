#pragma once

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Debug
{
    sf::Vector2i mousePosition;

    sf::Font font;
    sf::Text pausedLabel;
    sf::Text coordsLabel;

public:
    bool pausedLabelVisible = true;
    bool menu = false;

    Debug()
    {
        font.loadFromFile("../fonts/bit5x3.ttf");

        // Paused label
        pausedLabel.setString("Paused");
        pausedLabel.setFont(font);
        pausedLabel.setCharacterSize(textSize);
        pausedLabel.setFillColor(textColor);
        pausedLabel.setPosition(10, height - textSize - 10);

        // Coords label
        coordsLabel.setFont(font);
        coordsLabel.setCharacterSize(15);
        coordsLabel.setFillColor(textColor);
        coordsLabel.setPosition(10, 10);
    }

    void updatePausedLabel();
    void renderPausedLabel(sf::RenderWindow &window);
    void toggleMenu();
    void updateCoords(const sf::RenderWindow &window);
    void updateMenu();
    void renderMenu(sf::RenderWindow &window);

};