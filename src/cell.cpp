#include "cell.hpp"

#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

int Cell::atPos(const float &pos_x, const float &pos_y, const std::vector<Cell> &cellVector)
{
    for (int i = 0; i < cellVector.size(); i++)
    {
        if (cellVector[i].pos.x == pos_x && cellVector[i].pos.y == pos_y) return i;
    }
    return -1;
}

void Cell::spawnCell(const int &col, const int &row, std::unordered_map<sf::Vector2f, Cell, Vector2fHash, Vector2fEqual> &cellMap)
{
    const int x_pos = col * SIZE;
    const int y_pos = row * SIZE;
    const int index = Cell::atPos(x_pos, y_pos, cellVector);

    if (index == -1) cellVector.push_back(Cell(x_pos, y_pos, SIZE));
    else cellVector.erase(cellVector.begin() + index);
}

void Cell::render(sf::RenderWindow &window)
{
    window.draw(rect);
}