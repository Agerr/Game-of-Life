#include "debug.hpp"

#include <SFML/Graphics.hpp>

#include <string>

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

    // Paused label
    const std::string text = coordsLabel.getString();
    window.draw(coordsLabel);
}