#include "debug.hpp"

#include "camera.hpp"
#include "clock.hpp"
#include "grid.hpp"
#include "mouse.hpp"

#include <SFML/Graphics.hpp>

#include <cmath>
#include <string>

sf::Font Debug::font;

sf::Text Debug::pausedLabel;
sf::Text Debug::gridPosLabel;
sf::Text Debug::zoomFactorLabel;
sf::Text Debug::cellCountLabel;
sf::Text Debug::worldPosLabel;
sf::Text Debug::screenPosLabel;

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

void Debug::updateMenu()
{
    const std::string gridPosString = "Grid\tX: " + std::to_string(Mouse::gridPos.x) + "\tY: " + std::to_string(Mouse::gridPos.y);
    gridPosLabel.setString(gridPosString);

    const std::string zoomFactorString = "Zoom\t" + roundToDecimalPlaces(Camera::zoomFactor, 2) + "x";
    zoomFactorLabel.setString(zoomFactorString);

    const std::string cellCountString = "Cells\t" + std::to_string(Grid::cellCount());
    cellCountLabel.setString(cellCountString);

    const std::string worldPosString = "World\t X: " + roundToDecimalPlaces(Mouse::worldPos.x, 0) + "\tY: " + roundToDecimalPlaces(Mouse::worldPos.y, 0);
    worldPosLabel.setString(worldPosString);

    const std::string mousePosString = "Screen\tX: " + std::to_string(Mouse::screenPos.x) + "\tY: " + std::to_string(Mouse::screenPos.y);
    screenPosLabel.setString(mousePosString);
}

void Debug::renderMenu(sf::RenderWindow &window)
{
    window.draw(gridPosLabel);
    window.draw(zoomFactorLabel);
    window.draw(cellCountLabel);
    window.draw(worldPosLabel);
    window.draw(screenPosLabel);
}