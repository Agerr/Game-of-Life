#include "cell.hpp"

#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

Cell* Cell::getCell(const float& pos_x, const float& pos_y, CellMap& cellMap)
{
    const sf::Vector2f pos(pos_x, pos_y);

    auto it = cellMap.find(pos);
    if (it != cellMap.end())
    {
        return &(it->second);
    }
    return nullptr;
}

void Cell::toggleCell(const int &col, const int &row, CellMap &cellMap)
{
    const int cols = WIDTH / SIZE;
    const int rows = HEIGHT / SIZE;
    if (col < 0 || col >= cols || row < 0 || row >= rows) return;

    const int pos_x = col * SIZE;
    const int pos_y = row * SIZE;

    Cell* cellptr = Cell::getCell(pos_x, pos_y, cellMap);

    if (cellptr == nullptr)
    {
        cellMap.emplace(sf::Vector2f(pos_x, pos_y), Cell(pos_x, pos_y, SIZE));
    }
    else
    {
        cellMap.erase(sf::Vector2f(pos_x, pos_y));
    }
}

void Cell::render(sf::RenderWindow &window)
{
    window.draw(rect);
}