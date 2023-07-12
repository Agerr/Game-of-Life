#pragma once

#include "aliveCellsSet.hpp"
#include "neighbourCellMap.hpp"

#include <SFML/Graphics.hpp>

class Grid
{
    static AliveCellsSet aliveCells;
    static NeighbourCellMap neighbourCells;

    static sf::RectangleShape cellRectangle;

public:
    static int cellCount();
    static void toggleCell(const sf::Vector2i &gridPos);
    static void update();
    static void render(sf::RenderWindow &window);
};