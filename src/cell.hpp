#pragma once

#include "cellMap.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

class Cell
{
    sf::RectangleShape rect;

public:
    sf::Vector2f pos;

    Cell(const float &pos_x, const float &pos_y, const float &size)
    {
        pos = sf::Vector2f(pos_x, pos_y);

        rect.setPosition(pos);
        rect.setSize(sf::Vector2f(size, size));
        rect.setFillColor(sf::Color::White);
    }

    static Cell* getCell(const float& pos_x, const float& pos_y, CellMap& cellMap);
    static void toggleCell(const int &col, const int &row, CellMap &cellMap);
    void render(sf::RenderWindow &window);
};