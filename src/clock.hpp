#pragma once

#include "config.hpp"

#include <SFML/Graphics.hpp>

class Clock
{
    static sf::Clock clock;

    static const sf::Time updateFrequency;
    static sf::Time timeSinceGameUpdate;

    static const sf::Time blinkFrequency;
    static sf::Time timeSinceBlink;

public:
    static void updateClock();
    static bool blink();
    static bool gameUpdate();
};