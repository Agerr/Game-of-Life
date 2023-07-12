#include "grid.hpp"

#include "config.hpp"
#include "Vector2iHash.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_set>

std::unordered_set<sf::Vector2i, Vector2iHash> Grid::aliveCells;

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

void Grid::render(sf::RenderWindow &window)
{
    for (const sf::Vector2i &gridPos: aliveCells)
    {
        cellRectangle.setPosition(sf::Vector2f(gridPos.x * size, gridPos.y * size));
        window.draw(cellRectangle);
    }
}