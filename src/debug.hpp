#pragma once

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Debug
{
    static sf::Vector2i mousePos;

    static sf::Font font;
    static sf::Text pausedLabel;
    static sf::Text worldCoordsLabel;
    static sf::Text mouseCoordsLabel;

public:
    static bool pausedLabelVisible;
    static bool menu;

    static void init(const sf::RenderWindow &window)
    {
        font.loadFromFile("../fonts/bit5x3.ttf");

        // Paused label
        pausedLabel.setString("Paused");
        pausedLabel.setFont(font);
        pausedLabel.setCharacterSize(textSize);
        pausedLabel.setFillColor(textColor);
        pausedLabel.setPosition(10, height - textSize - 10);

        // World coords label
        worldCoordsLabel.setFont(font);
        worldCoordsLabel.setCharacterSize(15);
        worldCoordsLabel.setFillColor(textColor);
        worldCoordsLabel.setPosition(10, 10);

        // Mouse coords label
        mouseCoordsLabel.setFont(font);
        mouseCoordsLabel.setCharacterSize(15);
        mouseCoordsLabel.setFillColor(textColor);
        mouseCoordsLabel.setPosition(10, 30);

        pausedLabelVisible = true;
        menu = false;

        Debug::updateCoords(window);
    }

    static void updatePausedLabel();
    static void renderPausedLabel(sf::RenderWindow &window);
    static void toggleMenu();
    static void updateCoords(const sf::RenderWindow &window);
    static void updateMenu(const sf::RenderWindow &window);
    static void renderMenu(sf::RenderWindow &window);
};