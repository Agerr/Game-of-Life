#pragma once

#include "Vector2iHash.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_set>

class Grid
{
    static std::unordered_set<sf::Vector2i, Vector2iHash> aliveCells;

    static sf::RectangleShape cellRectangle;

public:
    static int cellCount();
    static void toggleCell(const sf::Vector2i &gridPos);
    static void render(sf::RenderWindow &window);
};