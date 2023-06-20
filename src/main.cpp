#include "cell.hpp"
#include "cellMap.hpp"
#include "clock.hpp"
#include "config.hpp"
#include "debug.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    // Window
    sf::VideoMode videoMode = sf::VideoMode(width, height);
    if (fullscreen) videoMode = sf::VideoMode::getFullscreenModes()[0];

    sf::RenderWindow window(videoMode, windowName);
    window.setFramerateLimit(fpsLimit);
    window.setVerticalSyncEnabled(vSync);

    sf::View view = window.getDefaultView();

    Debug::init();
    Debug::updatePositions(window);

    CellMap cellMap;

    bool isPaused = true;
    bool leftPressed = false;
    float zoomFactor = 1;
    sf::Vector2i initialMousePos;
    sf::Vector2i currentMousePos;
    sf::Vector2i lastMousePos;

    // Game loop
    while (window.isOpen())
    {
        // Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed                  :   window.close();         break;
                
                // Keyboard events
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape       :   window.close();         break;
                        case sf::Keyboard::F1           :   Debug::toggleMenu();    break;
                        case sf::Keyboard::Space        :   isPaused = !isPaused;   break;
                    }
                    break;

                // Mouse events
                case sf::Event::MouseButtonPressed:
                    initialMousePos = sf::Mouse::getPosition(window);
                    lastMousePos = initialMousePos;

                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            leftPressed = true;
                            break;
                    }
                    break;

                case sf::Event::MouseButtonReleased:
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            leftPressed = false;

                            if (initialMousePos - lastMousePos == sf::Vector2i(0, 0))
                            {
                                Cell::toggleCell(Debug::gridPos, cellMap);
                            }
                            break;
                    }
                    break;

                case sf::Event::MouseMoved:
                    currentMousePos = sf::Mouse::getPosition(window);

                    if (leftPressed)
                    {
                        const sf::Vector2f draggingOffset = sf::Vector2f(currentMousePos - lastMousePos);
                        view.move(-draggingOffset.x / zoomFactor, -draggingOffset.y / zoomFactor);                     
                    }

                    lastMousePos = currentMousePos;
                    Debug::updatePositions(window);
                    break;

                case sf::Event::MouseWheelScrolled:
                    const sf::Vector2f worldPosBeforeZoom = window.mapPixelToCoords(lastMousePos, view);

                    if (event.mouseWheelScroll.delta > 0)
                    {
                        if (zoomFactor < maxZoom) view.zoom(1 - zoomStrength);
                    }
                    else
                    {
                        if (zoomFactor > minZoom) view.zoom(1 + zoomStrength);
                    }

                    zoomFactor = window.getSize().x / view.getSize().x;

                    if (zoomFactor > maxZoom) view.zoom(zoomFactor / maxZoom);
                    else if (zoomFactor < minZoom) view.zoom(zoomFactor / minZoom);
                    zoomFactor = window.getSize().x / view.getSize().x;

                    const sf::Vector2f worldPosAfterZoom = window.mapPixelToCoords(lastMousePos, view);
                    view.move(worldPosBeforeZoom - worldPosAfterZoom);
                    break;
            }
        }

        // Logic
        Clock::updateClock();
        Debug::updatePausedLabel();
        if (Debug::menu) Debug::updateMenu(zoomFactor);

        while (Clock::gameUpdate())
        {
            if (!isPaused) Cell::updateMap(cellMap);
        }

        // Render
        window.clear();

        // Fixed
        window.setView(window.getDefaultView());
        if (isPaused && Debug::pausedLabelVisible) Debug::renderPausedLabel(window);
        if (Debug::menu) Debug::renderMenu(window);

        // Grid
        window.setView(view);
        Cell::render(window, cellMap);

        window.display();
    }

    return 0;
}