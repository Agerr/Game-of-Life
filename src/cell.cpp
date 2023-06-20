#include "cell.hpp"

#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>

const int dx[] = {  -1, 0,  1,  -1, 1,  -1, 0,  1   };
const int dy[] = {  -1, -1, -1, 0,  0,  1,  1,  1   };

Cell* Cell::getCell(const sf::Vector2i &gridPos, CellMap& cellMap)
{
    auto it = cellMap.find(gridPos);
    if (it != cellMap.end())
    {
        return &(it->second);
    }
    return nullptr;
}

void Cell::toggleCell(const sf::Vector2i &gridPos, CellMap &cellMap)
{
    Cell* cellptr = Cell::getCell(gridPos, cellMap);

    if (cellptr == nullptr)
    {
        cellMap.emplace(gridPos, Cell(gridPos));
    }
    else
    {
        cellMap.erase(gridPos);
    }
}

int Cell::neighbourCount(const sf::Vector2i &gridPos, CellMap &cellMap)
{
    int count = 0;

    for (int i = 0; i < sizeof(dx) / sizeof(dx[0]); i++)
    {
        const sf::Vector2i neighbourPos = gridPos + sf::Vector2i(dx[i], dy[i]);

        if (Cell::getCell(neighbourPos, cellMap) != nullptr) count++;
    }
    return count;
}

bool Cell::willBecomeAlive(const sf::Vector2i &gridPos, CellMap &cellMap)
{
    const int neighbourCount = Cell::neighbourCount(gridPos, cellMap);

    return (neighbourCount >= reproduction_bound && neighbourCount <= overpopulation_bound);
}

void Cell::updateMap(CellMap &cellMap)
{
    CellMap newCellMap = cellMap;

    for (auto &pair : cellMap)
    {
        Cell cell = pair.second;

        const int neighbourCount = Cell::neighbourCount(cell.gridPos, cellMap);
        
        if (neighbourCount < underpopulation_bound || neighbourCount > overpopulation_bound)
        {
            Cell::toggleCell(cell.gridPos, newCellMap);
        }

        for (int i = 0; i < sizeof(dx) / sizeof(dx[0]); i++)
        {
            const sf::Vector2i neighbourPos = cell.gridPos + sf::Vector2i(dx[i], dy[i]);
            
            if (Cell::getCell(neighbourPos, cellMap) != nullptr) continue;

            if (willBecomeAlive(neighbourPos, cellMap))
            {
                Cell::toggleCell(neighbourPos, newCellMap);
            }
        }
    }

    cellMap = newCellMap;
}

void Cell::render(sf::RenderWindow &window, const CellMap &cellMap)
{
    for (auto &pair : cellMap) window.draw(pair.second.rect);
}