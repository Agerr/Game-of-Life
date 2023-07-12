#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_set>

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

using cellsSet = std::unordered_set<sf::Vector2i, Vector2iHash>;