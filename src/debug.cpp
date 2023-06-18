#include "debug.hpp"

#include "cell.hpp"
#include "clock.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <cmath>
#include <string>

sf::Vector2i Debug::mousePos;
sf::Font Debug::font;
sf::Text Debug::pausedLabel;
sf::Text Debug::gridCoordsLabel;
sf::Text Debug::zoomFactorLabel;
sf::Text Debug::worldCoordsLabel;
sf::Text Debug::mouseCoordsLabel;
bool Debug::pausedLabelVisible;
bool Debug::menu;

float roundToPrecision(float number, int precision)
{
    float factor = std::pow(10, precision);
    return std::round(number * factor) / factor;
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

void Debug::updateCoords(const sf::Vector2i &lastMousePos)
{
    mousePos = lastMousePos;
}
void Debug::updateMenu(const sf::RenderWindow &window, const float &zoomFactor)
{
    const sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

    const int pressed_col = int(worldPos.x / size) - (worldPos.x < 0 ? 1 : 0);
    const int pressed_row = int(worldPos.y / size) - (worldPos.y < 0 ? 1 : 0);
    const std::string gridCoordsString = "Grid\tX: " + std::to_string(pressed_col) + "\tY: " + std::to_string(pressed_row);
    gridCoordsLabel.setString(gridCoordsString);

    const std::string zoomFactorRounded = std::to_string(roundToPrecision(zoomFactor, 2));
    const std::string zoomFactorSubtring = zoomFactorRounded.substr(0, zoomFactorRounded.find('.') + 3);
    const std::string zoomFactorString = "Zoom\t" + zoomFactorSubtring + "x";
    zoomFactorLabel.setString(zoomFactorString);

    const std::string worldCoordsString = "World\tX: " + std::to_string(int(worldPos.x)) + "\tY: " + std::to_string(int(worldPos.y));
    worldCoordsLabel.setString(worldCoordsString);

    const std::string mouseCoordsString = "Mouse\tX: " + std::to_string(mousePos.x) + "\tY: " + std::to_string(mousePos.y);
    mouseCoordsLabel.setString(mouseCoordsString);
}

void Debug::renderMenu(sf::RenderWindow &window)
{
    window.draw(gridCoordsLabel);
    window.draw(zoomFactorLabel);
    window.draw(worldCoordsLabel);
    window.draw(mouseCoordsLabel);
}