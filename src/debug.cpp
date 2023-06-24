#include "debug.hpp"

#include "cell.hpp"
#include "clock.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <cmath>
#include <string>

sf::Vector2i Debug::gridPos;
sf::Vector2f Debug::worldPos;
sf::Vector2i Debug::mousePos;

sf::Font Debug::font;
sf::Text Debug::pausedLabel;
sf::Text Debug::gridPosLabel;
sf::Text Debug::zoomFactorLabel;
sf::Text Debug::cellCountLabel;
sf::Text Debug::worldPosLabel;
sf::Text Debug::mousePosLabel;

bool Debug::pausedLabelVisible;
bool Debug::menu;

std::string roundToDecimalPlaces(float number, int places)
{
    const int factor = std::pow(10, places);
    const std::string rounded = std::to_string(std::round(number * factor) / factor);
    const std::string roundedSubstring = rounded.substr(0, rounded.find('.') + places + (places > 0 ? 1 : 0));
    
    return roundedSubstring;
}

void Debug::updatePausedLabel()
{
    if (Clock::blink()) pausedLabelVisible = !pausedLabelVisible;
}

void Debug::renderPausedLabel(sf::RenderWindow &window)
{
    window.draw(pausedLabel);
}

void Debug::toggleMenu()
{
    menu = !menu;
}

void Debug::updatePositions(const sf::RenderWindow &window)
{
    mousePos = sf::Mouse::getPosition(window);
    worldPos = window.mapPixelToCoords(mousePos);
    gridPos = sf::Vector2i(worldPos.x / size - (worldPos.x < 0 ? 1 : 0), worldPos.y / size - (worldPos.y < 0 ? 1 : 0));
}
void Debug::updateMenu(const float &zoomFactor)
{
    const std::string gridPosString = "Grid\tX: " + std::to_string(gridPos.x) + "\tY: " + std::to_string(gridPos.y);
    gridPosLabel.setString(gridPosString);

    const std::string zoomFactorString = "Zoom\t" + roundToDecimalPlaces(zoomFactor, 2) + "x";
    zoomFactorLabel.setString(zoomFactorString);

    const std::string cellCountString = "Cells\t" + std::to_string(Cell::getCount());
    cellCountLabel.setString(cellCountString);

    const std::string worldPosString = "World\tX: " + roundToDecimalPlaces(worldPos.x, 0) + "\tY: " + roundToDecimalPlaces(worldPos.y, 0);
    worldPosLabel.setString(worldPosString);

    const std::string mousePosString = "Mouse\tX: " + std::to_string(mousePos.x) + "\tY: " + std::to_string(mousePos.y);
    mousePosLabel.setString(mousePosString);
}

void Debug::renderMenu(sf::RenderWindow &window)
{
    window.draw(gridPosLabel);
    window.draw(zoomFactorLabel);
    window.draw(cellCountLabel);
    window.draw(worldPosLabel);
    window.draw(mousePosLabel);
}