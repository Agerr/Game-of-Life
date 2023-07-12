#pragma once

#include <SFML/Graphics.hpp>

struct Vector2iHash
{
    std::size_t operator()(const sf::Vector2i& vec) const
    {
        std::size_t seed = 0;
        seed ^= vec.x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= vec.y + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};