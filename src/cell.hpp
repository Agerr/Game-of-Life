#pragma once

#include <SFML/Graphics.hpp>

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

    static int atPos(const float pos_x, const float pos_y, const std::vector<Cell> &cellVector);
    void render(sf::RenderWindow &window);
};