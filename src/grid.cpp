#include "grid.hpp"

#include "cellsSet.hpp"
#include "config.hpp"
#include "neighbourCellMap.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_set>

cellsSet Grid::aliveCells;
NeighbourCellMap Grid::neighbourCells;

sf::RectangleShape Grid::cellRectangle = [](){
    sf::RectangleShape rect(sf::Vector2f(size, size));
    rect.setFillColor(sf::Color::White);
    return rect;
}();

int Grid::cellCount()
{
    return aliveCells.size();
}

void Grid::toggleCell(const sf::Vector2i &gridPos)
{
    if (aliveCells.count(gridPos) == 0)
        aliveCells.insert(gridPos);
    else
        aliveCells.erase(gridPos);
}

void Grid::updateNeighbourMap()
{
    neighbourCells.clear();

    for (const sf::Vector2i &gridPos : aliveCells)
    {
        for (int i = 0; i < sizeof(dx) / sizeof(dx[0]); i++)
        {
            const sf::Vector2i neighbourPos = gridPos + sf::Vector2i(dx[i], dy[i]);
            neighbourCells[neighbourPos]++;
        }
    }
}

void Grid::updateGrid()
{
    Grid::updateNeighbourMap();

    cellsSet nextGeneration;

    for (const auto &pair : neighbourCells)
    {
        if (pair.second < underpopulation_bound || pair.second > overpopulation_bound) continue;

        const bool alive = aliveCells.count(pair.first) == 1;
        if (!alive && pair.second < reproduction_bound) continue;

        nextGeneration.insert(pair.first);
    }

    aliveCells = nextGeneration;
}

void Grid::render(sf::RenderWindow &window)
{
    for (const sf::Vector2i &gridPos: aliveCells)
    {
        cellRectangle.setPosition(sf::Vector2f(gridPos.x * size, gridPos.y * size));
        window.draw(cellRectangle);
    }
}