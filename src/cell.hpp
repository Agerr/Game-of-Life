#pragma once

#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>

class Cell
{
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

    static Cell* getCell(const sf::Vector2i &gridPos, CellMap& cellMap);
    static void toggleCell(const sf::Vector2i &gridPos, CellMap &cellMap);
    static int neighbourCount(const sf::Vector2i &gridPos, CellMap &cellMap);
    static bool willBecomeAlive(const sf::Vector2i &gridPos, CellMap &cellMap);
    static void updateMap(CellMap &cellMap);
    static void render(sf::RenderWindow &window, const CellMap &cellMap);
};