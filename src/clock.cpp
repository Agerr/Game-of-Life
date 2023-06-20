#include "clock.hpp"

#include "config.hpp"

#include <SFML/Graphics.hpp>

sf::Clock Clock::clock;
const sf::Time Clock::updateFrequency = sf::seconds(1.0f / ups);
sf::Time Clock::timeSinceGameUpdate = sf::Time::Zero;
const sf::Time Clock::blinkFrequency = sf::seconds(1.0f / blinksPerSecond);
sf::Time Clock::timeSinceBlink = sf::Time::Zero;

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