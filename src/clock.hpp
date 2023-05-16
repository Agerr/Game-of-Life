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

sf::Clock Clock::clock;
const sf::Time Clock::updateFrequency = sf::seconds(1.0f / ups);
sf::Time Clock::timeSinceGameUpdate = sf::Time::Zero;
const sf::Time Clock::blinkFrequency = sf::seconds(1.0f / blinksPerSecond);
sf::Time Clock::timeSinceBlink = sf::Time::Zero;