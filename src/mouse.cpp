#include "mouse.hpp"

#include "config.hpp"

#include <SFML/Graphics.hpp>

sf::Vector2i Mouse::pressPos;
sf::Vector2i Mouse::prevScreenPos;

sf::Vector2i Mouse::gridPos;
sf::Vector2f Mouse::worldPos;
sf::Vector2i Mouse::screenPos;
float Mouse::zoomFactor = 1;

void Mouse::updatePositions(const sf::RenderWindow &window)
{
    prevScreenPos = screenPos;
    screenPos = sf::Mouse::getPosition(window);
    worldPos = window.mapPixelToCoords(screenPos);
    gridPos = sf::Vector2i(worldPos.x / size - (worldPos.x < 0 ? 1 : 0), worldPos.y / size - (worldPos.y < 0 ? 1 : 0));
}

void Mouse::updateZoomFactor(const sf::RenderWindow &window, const sf::View &view)
{
    zoomFactor = window.getSize().x / view.getSize().x;
}

void Mouse::mousePress(const sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Right)) return;
    pressPos = sf::Mouse::getPosition(window);
}

bool Mouse::mouseDragged()
{
    return (pressPos - screenPos != sf::Vector2i(0, 0));
}