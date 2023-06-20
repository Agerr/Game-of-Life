#include "cell.hpp"

#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>

CellMap Cell::cellMap;

Cell* Cell::getCell(const sf::Vector2i &gridPos)
{
    auto it = cellMap.find(gridPos);
    if (it != cellMap.end()) return &(it->second);
    return nullptr;
}

void Cell::toggleCell(const sf::Vector2i &gridPos, CellMap *cellMap)
{
    CellMap& mapptr = cellMap ? *cellMap : Cell::cellMap;
    Cell* cellptr = Cell::getCell(gridPos);

    if (cellptr == nullptr)
        mapptr.emplace(gridPos, Cell(gridPos));
    else
        mapptr.erase(gridPos);
}

int Cell::neighbourCount(const sf::Vector2i &gridPos)
{
    int count = 0;
    for (int i = 0; i < sizeof(dx) / sizeof(dx[0]); i++)
    {
        const sf::Vector2i neighbourPos = gridPos + sf::Vector2i(dx[i], dy[i]);

        if (Cell::getCell(neighbourPos) != nullptr) count++;
    }
    return count;
}

bool Cell::willBecomeAlive(const sf::Vector2i &gridPos)
{
    const int neighbourCount = Cell::neighbourCount(gridPos);

    return (neighbourCount >= reproduction_bound && neighbourCount <= overpopulation_bound);
}

void Cell::updateMap()
{
    CellMap newCellMap = cellMap;
    
    for (auto &pair : cellMap)
    {
        const Cell cell = pair.second;
        const int neighbourCount = Cell::neighbourCount(cell.gridPos);

        if (neighbourCount < underpopulation_bound || neighbourCount > overpopulation_bound)
            Cell::toggleCell(cell.gridPos, &newCellMap);

        for (int i = 0; i < sizeof(dx) / sizeof(dx[0]); i++)
        {
            const sf::Vector2i neighbourPos = cell.gridPos + sf::Vector2i(dx[i], dy[i]);
            if (Cell::getCell(neighbourPos) != nullptr) continue;

            if (willBecomeAlive(neighbourPos))
                Cell::toggleCell(neighbourPos, &newCellMap);
        }
    }
    cellMap = newCellMap;
}

void Cell::render(sf::RenderWindow &window)
{
    for (auto &pair : cellMap) window.draw(pair.second.rect);
}