#include "debug.hpp"

#include "clock.hpp"

#include <SFML/Graphics.hpp>

#include <string>

sf::Vector2i Debug::mousePos;
sf::Font Debug::font;
sf::Text Debug::pausedLabel;
sf::Text Debug::worldCoordsLabel;
sf::Text Debug::mouseCoordsLabel;
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
    mousePos = sf::Mouse::getPosition(window);
}

void Debug::updateMenu(const sf::RenderWindow &window)
{
    const sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
    const std::string worldCoordsString = "World\tX: " + std::to_string(int(worldPos.x)) + "\tY: " + std::to_string(int(worldPos.y));
    worldCoordsLabel.setString(worldCoordsString);

    const std::string mouseCoordsString = "Mouse\tX: " + std::to_string(mousePos.x) + "\tY: " + std::to_string(mousePos.y);
    mouseCoordsLabel.setString(mouseCoordsString);
}

void Debug::renderMenu(sf::RenderWindow &window)
{
    updateMenu(window);

    worldCoordsLabel.setPosition(window.mapPixelToCoords(sf::Vector2i(10, 10)));
    mouseCoordsLabel.setPosition(window.mapPixelToCoords(sf::Vector2i(10, 30)));

    window.draw(worldCoordsLabel);
    window.draw(mouseCoordsLabel);
}