#pragma once

#include <SFML/Graphics.hpp>

class Mouse
{
    static sf::Vector2i pressPos;

public:
    static sf::Vector2i prevScreenPos;
    static sf::Vector2i gridPos;
    static sf::Vector2f worldPos;
    static sf::Vector2i screenPos;

    static void updatePositions(const sf::RenderWindow &window);
    static void mousePress(const sf::RenderWindow &window);
    static bool mouseDragged();
};