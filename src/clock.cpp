#include "clock.hpp"

#include <SFML/Graphics.hpp>

void Clock::updateClock()
{
    const sf::Time timeElapsed = clock.restart();
    timeSinceGameUpdate += timeElapsed;
    timeSinceBlink += timeElapsed;
}

bool Clock::blink()
{
    if (timeSinceBlink > blinkFrequency)
    {
        timeSinceBlink = sf::Time::Zero;
        return true;
    }
    return false;
}

bool Clock::gameUpdate()
{
    if (timeSinceGameUpdate > updateFrequency)
    {
        timeSinceGameUpdate -= updateFrequency;
        return true;
    }
    return false;
}