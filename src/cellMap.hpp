#pragma once

#include "cell.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>

struct Vector2fHash {
    std::size_t operator()(const sf::Vector2f& vec) const {
        std::size_t h1 = std::hash<float>()(vec.x);
        std::size_t h2 = std::hash<float>()(vec.y);
        return h1 ^ (h2 << 1);
    }
};

struct Vector2fEqual {
    bool operator()(const sf::Vector2f& v1, const sf::Vector2f& v2) const {
        return v1.x == v2.x && v1.y == v2.y;
    }
};

using CellMap = std::unordered_map<sf::Vector2f, Cell, Vector2fHash, Vector2fEqual>;