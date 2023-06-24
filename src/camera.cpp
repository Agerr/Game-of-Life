#include "camera.hpp"

#include "config.hpp"
#include "mouse.hpp"

#include <SFML/Graphics.hpp>

sf::View Camera::view;
float Camera::zoomFactor = 1;

void Camera::setView(sf::RenderWindow &window)
{
    window.setView(view);
}

void Camera::updateZoomFactor(const sf::RenderWindow &window)
{
    zoomFactor = window.getSize().x / view.getSize().x;
}

void Camera::move(const sf::Vector2f &screenOffset)
{
    const sf::Vector2f scaledOffset = sf::Vector2f(screenOffset.x / zoomFactor, screenOffset.y / zoomFactor);
    view.move(scaledOffset);
}

void Camera::zoom(const bool &direction, const sf::RenderWindow &window)
{
    const sf::Vector2f worldPosBeforeZoom = window.mapPixelToCoords(Mouse::screenPos, view);

    view.zoom(1 + (direction ? zoomStrength : -zoomStrength));

    Camera::updateZoomFactor(window);
    if (zoomFactor > maxZoom)
    {
        view.zoom(zoomFactor / maxZoom);
        Camera::updateZoomFactor(window);
    }
    else if (zoomFactor < minZoom)
    {
        view.zoom(zoomFactor / minZoom);
        Camera::updateZoomFactor(window);
    }

    const sf::Vector2f worldPosAfterZoom = window.mapPixelToCoords(Mouse::screenPos, view);
    view.move(worldPosBeforeZoom - worldPosAfterZoom);
}