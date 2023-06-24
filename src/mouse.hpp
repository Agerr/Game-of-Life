#pragma once

#include <SFML/Graphics.hpp>

class Mouse
{
public:
    static sf::Vector2i gridPos;
    static sf::Vector2f worldPos;
    static sf::Vector2i screenPos;
    static float zoomFactor;

    static void updatePosition(const sf::RenderWindow &window);
    static void updateZoomFactor(const sf::RenderWindow &window, const sf::View &view);
};