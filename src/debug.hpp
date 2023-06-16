#pragma once

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Debug
{
    static sf::Vector2i mousePosition;

    static sf::Font font;
    static sf::Text pausedLabel;
    static sf::Text MouseCoordsLabel;

public:
    static bool pausedLabelVisible;
    static bool menu;

    static void init()
    {
        font.loadFromFile("../fonts/bit5x3.ttf");

        // Paused label
        pausedLabel.setString("Paused");
        pausedLabel.setFont(font);
        pausedLabel.setCharacterSize(textSize);
        pausedLabel.setFillColor(textColor);
        pausedLabel.setPosition(10, height - textSize - 10);

        // Mouse coords label
        MouseCoordsLabel.setFont(font);
        MouseCoordsLabel.setCharacterSize(15);
        MouseCoordsLabel.setFillColor(textColor);
        MouseCoordsLabel.setPosition(10, 10);

        pausedLabelVisible = true;
        menu = false;
    }

    static void updatePausedLabel();
    static void renderPausedLabel(sf::RenderWindow &window);
    static void toggleMenu();
    static void updateCoords(const sf::RenderWindow &window);
    static void updateMenu();
    static void renderMenu(sf::RenderWindow &window);
};