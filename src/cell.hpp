#pragma once

#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>

class Cell
{
    static CellMap cellMap;

    sf::RectangleShape rect;

public:
    sf::Vector2i gridPos;
    sf::Vector2f pos;

    Cell(const sf::Vector2i &gridPos)
    {
        this->gridPos = gridPos;
        pos = sf::Vector2f(gridPos.x * size, gridPos.y * size);

        rect.setPosition(pos);
        rect.setSize(sf::Vector2f(size, size));
        rect.setFillColor(sf::Color::White);
    }

    static Cell* getCell(const sf::Vector2i &gridPos);
    static void toggleCell(const sf::Vector2i &gridPos, CellMap *cellMap);
    static int neighbourCount(const sf::Vector2i &gridPos);
    static bool willBecomeAlive(const sf::Vector2i &gridPos);
    static void updateMap();
    static void render(sf::RenderWindow &window);
};