#pragma once

#include <SFML/Graphics.hpp>

class Clock
{
    static sf::Clock clock;

    static sf::Time updateFrequency;
    static sf::Time timeSinceGameUpdate;

    static const sf::Time blinkFrequency;
    static sf::Time timeSinceBlink;

public:
    static int ups;

    static void changeUps(const bool &increase);
    static void updateClock();
    static bool blink();
    static bool gameUpdate();
};