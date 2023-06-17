#pragma once

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Debug
{
    static sf::Vector2i mousePos;

    static sf::Font font;
    static sf::Text pausedLabel;
    static sf::Text gridCoordsLabel;
    static sf::Text zoomFactorLabel;
    static sf::Text worldCoordsLabel;
    static sf::Text mouseCoordsLabel;

public:
    static bool pausedLabelVisible;
    static bool menu;

    static void init(const sf::Vector2i &lastMousePos)
    {
        font.loadFromFile("../fonts/bit5x3.ttf");

        // Paused label
        pausedLabel.setString("Paused");
        pausedLabel.setFont(font);
        pausedLabel.setCharacterSize(textSize);
        pausedLabel.setFillColor(textColor);
        pausedLabel.setPosition(10, height - textSize - 10);

        // Grid coords label
        gridCoordsLabel.setFont(font);
        gridCoordsLabel.setCharacterSize(15);
        gridCoordsLabel.setFillColor(textColor);
        gridCoordsLabel.setPosition(10, 10);

        // Zoom factor label
        zoomFactorLabel.setFont(font);
        zoomFactorLabel.setCharacterSize(15);
        zoomFactorLabel.setFillColor(textColor);
        zoomFactorLabel.setPosition(10, 40);

        // World coords label
        worldCoordsLabel.setFont(font);
        worldCoordsLabel.setCharacterSize(15);
        worldCoordsLabel.setFillColor(textColor);
        worldCoordsLabel.setPosition(10, 70);

        // Mouse coords label
        mouseCoordsLabel.setFont(font);
        mouseCoordsLabel.setCharacterSize(15);
        mouseCoordsLabel.setFillColor(textColor);
        mouseCoordsLabel.setPosition(10, 100);

        pausedLabelVisible = true;
        menu = false;

        Debug::updateCoords(lastMousePos);
    }

    static void updatePausedLabel();
    static void renderPausedLabel(sf::RenderWindow &window);
    static void toggleMenu();
    static void updateCoords(const sf::Vector2i &lastMousePos);
    static void updateMenu(const sf::RenderWindow &window, const float &zoomFactor);
    static void renderMenu(sf::RenderWindow &window);
};