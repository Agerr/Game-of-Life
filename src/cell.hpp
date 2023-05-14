#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

class Cell
{
    sf::RectangleShape rect;

public:
    sf::Vector2f pos;

    Cell(const float &pos_x, const float &pos_y, const float &size)
    {
        pos = sf::Vector2f(pos_x, pos_y);

        rect.setPosition(pos);
        rect.setSize(sf::Vector2f(size, size));
        rect.setFillColor(sf::Color::White);
    }

    static int atPos(const float &pos_x, const float &pos_y, const std::vector<Cell> &cellVector);
    static void spawnCell(const int &col, const int &row, std::unordered_map<sf::Vector2f, Cell, Vector2fHash, Vector2fEqual> &cellMap);
    void render(sf::RenderWindow &window);
};