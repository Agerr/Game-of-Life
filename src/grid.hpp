#pragma once

#include "cellsSet.hpp"
#include "neighbourCellMap.hpp"

#include <SFML/Graphics.hpp>

class Grid
{
    static cellsSet aliveCells;
    static NeighbourCellMap neighbourCells;

    static sf::RectangleShape cellRectangle;

public:
    static int cellCount();
    static void toggleCell(const sf::Vector2i &gridPos);
    static void updateNeighbourMap();
    static void updateGrid();
    static void render(sf::RenderWindow &window);
};