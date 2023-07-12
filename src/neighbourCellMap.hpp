#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

struct Vector2Hash {
    std::size_t operator()(const sf::Vector2i& vector) const {
        std::size_t seed = 0;
        std::hash<int> hasher;
        seed ^= hasher(vector.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hasher(vector.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

struct Vector2Equal {
    bool operator()(const sf::Vector2i& vector1, const sf::Vector2i& vector2) const {
        return vector1.x == vector2.x && vector1.y == vector2.y;
    }
};

using NeighbourCellMap = std::unordered_map<sf::Vector2i, int, Vector2Hash, Vector2Equal>;