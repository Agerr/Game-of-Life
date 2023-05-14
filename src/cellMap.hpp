#pragma once

#include "cell.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>

class Cell;

struct Vector2Hash {
    std::size_t operator()(const sf::Vector2i& vec) const {
        std::size_t h1 = std::hash<int>()(vec.x);
        std::size_t h2 = std::hash<int>()(vec.y);
        return h1 ^ (h2 << 1);
    }
};

struct Vector2Equal {
    bool operator()(const sf::Vector2i& v1, const sf::Vector2i& v2) const {
        return v1.x == v2.x && v1.y == v2.y;
    }
};

using CellMap = std::unordered_map<sf::Vector2i, Cell, Vector2Hash, Vector2Equal>;