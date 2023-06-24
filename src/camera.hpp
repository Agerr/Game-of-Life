#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
    static sf::View view;

public:
    static float zoomFactor;

    static void init(sf::RenderWindow &window)
    {
        view = window.getDefaultView();
    }

    static void setView(sf::RenderWindow &window);
    static void updateZoomFactor(const sf::RenderWindow &window);
    static void move(const sf::Vector2f &screenOffset);
    static void zoom(const bool &direction, const sf::RenderWindow &window);
};