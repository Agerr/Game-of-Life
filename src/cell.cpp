#include "cell.hpp"

#include <SFML/Graphics.hpp>

int Cell::atPos(const float pos_x, const float pos_y, const std::vector<Cell> &cellVector)
{
    for (int i = 0; i < cellVector.size(); i++)
    {
        if (cellVector[i].pos.x == pos_x && cellVector[i].pos.y == pos_y) return i;
    }
    return -1;
}

void Cell::render(sf::RenderWindow &window)
{
    window.draw(rect);
}