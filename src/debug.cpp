#include "debug.hpp"

#include "clock.hpp"

#include <SFML/Graphics.hpp>

#include <string>

sf::Vector2i Debug::mousePosition;
sf::Font Debug::font;
sf::Text Debug::pausedLabel;
sf::Text Debug::coordsLabel;
bool Debug::pausedLabelVisible;
bool Debug::menu;

void Debug::updatePausedLabel()
{
    if (Clock::blink()) pausedLabelVisible = !pausedLabelVisible;
}

void Debug::renderPausedLabel(sf::RenderWindow &window)
{
    pausedLabel.setPosition(window.mapPixelToCoords(sf::Vector2i(10, height - textSize - 10)));
    window.draw(pausedLabel);
}

void Debug::toggleMenu()
{
    menu = !menu;
}

void Debug::updateCoords(const sf::RenderWindow &window)
{
    mousePosition = sf::Mouse::getPosition(window);
}

void Debug::updateMenu()
{
    const std::string coordsString = "X: " + std::to_string(mousePosition.x) + " Y: " + std::to_string(mousePosition.y);
    coordsLabel.setString(coordsString);
}

void Debug::renderMenu(sf::RenderWindow &window)
{
    updateMenu();

    coordsLabel.setPosition(window.mapPixelToCoords(sf::Vector2i(10, 10)));
    window.draw(coordsLabel);
}