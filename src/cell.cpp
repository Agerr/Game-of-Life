#include "cell.hpp"

#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

const int dx[] = {  -1, 0,  1,  -1, 1,  -1, 0,  1   };
const int dy[] = {  -1, -1, -1, 0,  0,  1,  1,  1   };

Cell* Cell::getCell(const int& col, const int& row, CellMap& cellMap)
{
    const sf::Vector2i pos(col, row);

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

    Cell* cellptr = Cell::getCell(col, row, cellMap);

    if (cellptr == nullptr)
    {
        cellMap.emplace(sf::Vector2i(col, row), Cell(col, row));
    }
    else
    {
        cellMap.erase(sf::Vector2i(col, row));
    }
}

int Cell::neighbourCount(const int &col, const int &row, CellMap &cellMap)
{
    int count = 0;

    for (int i = 0; i < sizeof(dx) / sizeof(dx[0]); i++)
    {
        const int neighbour_x = col + dx[i];
        const int neighbour_y = row + dy[i];

        if (Cell::getCell(neighbour_x, neighbour_y, cellMap) != nullptr) count++;
    }
    return count;
}

bool Cell::willBecomeAlive(const int &col, const int &row, CellMap &cellMap)
{
    const int neighbourCount = Cell::neighbourCount(col, row, cellMap);

    if (neighbourCount >= REPRODUCTION_BOUND && neighbourCount <= OVERPOPULATION_BOUND) return true;
    return false;
}

void Cell::updateMap(CellMap &cellMap)
{
    CellMap newCellMap = cellMap;

    for (auto &pair : cellMap)
    {
        Cell cell = pair.second;

        const int neighbourCount = Cell::neighbourCount(cell.pos_grid.x, cell.pos_grid.y, cellMap);
        
        if (neighbourCount < UNDERPOPULATION_BOUND || neighbourCount > OVERPOPULATION_BOUND)
        {
            Cell::toggleCell(cell.pos_grid.x, cell.pos_grid.y, newCellMap);
        }

        for (int i = 0; i < sizeof(dx) / sizeof(dx[0]); i++)
        {
            const int neighbour_x = cell.pos_grid.x + dx[i];
            const int neighbour_y = cell.pos_grid.y + dy[i];
            
            if (Cell::getCell(neighbour_x, neighbour_y, cellMap) != nullptr) continue;

            if (willBecomeAlive(neighbour_x, neighbour_y, cellMap))
            {
                Cell::toggleCell(neighbour_x, neighbour_y, newCellMap);
            }
        }
    }

    cellMap = newCellMap;
}

void Cell::render(sf::RenderWindow &window)
{
    window.draw(rect);
}