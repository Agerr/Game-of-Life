#pragma once

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Debug
{
    static sf::Font font;
    
    static sf::Text pausedLabel;
    static sf::Text gridPosLabel;
    static sf::Text zoomFactorLabel;
    static sf::Text cellCountLabel;
    static sf::Text worldPosLabel;
    static sf::Text screenPosLabel;

public:
    static bool pausedLabelVisible;
    static bool menu;

    static void init()
    {
        font.loadFromFile("../fonts/bit5x3.ttf");

        pausedLabel.setString("Paused");
        pausedLabel.setFont(font);
        pausedLabel.setCharacterSize(textSize);
        pausedLabel.setFillColor(textColor);
        pausedLabel.setPosition(10, height - textSize - 10);

        gridPosLabel.setFont(font);
        gridPosLabel.setCharacterSize(15);
        gridPosLabel.setFillColor(textColor);
        gridPosLabel.setPosition(10, 10);

        zoomFactorLabel.setFont(font);
        zoomFactorLabel.setCharacterSize(15);
        zoomFactorLabel.setFillColor(textColor);
        zoomFactorLabel.setPosition(10, 40);

        cellCountLabel.setFont(font);
        cellCountLabel.setCharacterSize(15);
        cellCountLabel.setFillColor(textColor);
        cellCountLabel.setPosition(10, 70);

        worldPosLabel.setFont(font);
        worldPosLabel.setCharacterSize(15);
        worldPosLabel.setFillColor(textColor);
        worldPosLabel.setPosition(10, 130);

        screenPosLabel.setFont(font);
        screenPosLabel.setCharacterSize(15);
        screenPosLabel.setFillColor(textColor);
        screenPosLabel.setPosition(10, 160);

        pausedLabelVisible = true;
        menu = false;
    }

    static void updatePausedLabel();
    static void renderPausedLabel(sf::RenderWindow &window);
    static void toggleMenu();
    static void updateMenu();
    static void renderMenu(sf::RenderWindow &window);
};