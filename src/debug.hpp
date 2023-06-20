#pragma once

#include <SFML/Graphics.hpp>

class Debug
{
    static sf::Font font;
    static sf::Text pausedLabel;
    static sf::Text gridPosLabel;
    static sf::Text zoomFactorLabel;
    static sf::Text worldPosLabel;
    static sf::Text mousePosLabel;

public:
    static sf::Vector2i gridPos;
    static sf::Vector2f worldPos;
    static sf::Vector2i mousePos;
    
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

        worldPosLabel.setFont(font);
        worldPosLabel.setCharacterSize(15);
        worldPosLabel.setFillColor(textColor);
        worldPosLabel.setPosition(10, 70);

        mousePosLabel.setFont(font);
        mousePosLabel.setCharacterSize(15);
        mousePosLabel.setFillColor(textColor);
        mousePosLabel.setPosition(10, 100);

        pausedLabelVisible = true;
        menu = false;
    }

    static void updatePausedLabel();
    static void renderPausedLabel(sf::RenderWindow &window);
    static void toggleMenu();
    static void updatePositions(const sf::RenderWindow &window);
    static void updateMenu(const float &zoomFactor);
    static void renderMenu(sf::RenderWindow &window);
};