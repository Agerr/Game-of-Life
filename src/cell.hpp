#pragma once

#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

class Cell
{
    sf::RectangleShape rect;

public:
    sf::Vector2i pos_grid;
    sf::Vector2f pos;

    Cell(const int &col, const int &row)
    {
        pos_grid = sf::Vector2i(col, row);
        pos = sf::Vector2f(col * SIZE, row * SIZE);

        rect.setPosition(pos);
        rect.setSize(sf::Vector2f(SIZE, SIZE));
        rect.setFillColor(sf::Color::White);
    }

    static Cell* getCell(const int& col, const int& row, CellMap& cellMap);
    static void toggleCell(const int &col, const int &row, CellMap &cellMap);
    static int neighbourCount(const int &pos_x, const int &pos_y, CellMap &cellMap);
    static bool willBecomeAlive(const int &col, const int &row, CellMap &cellMap);
    static void updateMap(CellMap &cellMap);
    void render(sf::RenderWindow &window);
};