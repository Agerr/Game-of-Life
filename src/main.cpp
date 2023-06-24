#include "cell.hpp"
#include "clock.hpp"
#include "config.hpp"
#include "debug.hpp"
#include "mouse.hpp"

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
    Mouse::updatePosition(window);

    bool isPaused = true;
    bool leftPressed = false;
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
                                Cell::toggleCell(Mouse::gridPos, nullptr);
                            break;
                    }
                    break;

                case sf::Event::MouseMoved:
                    Mouse::updatePosition(window);

                    if (leftPressed)
                    {
                        const sf::Vector2f draggingOffset = sf::Vector2f(Mouse::screenPos - lastMousePos);
                        view.move(-draggingOffset.x / Mouse::zoomFactor, -draggingOffset.y / Mouse::zoomFactor);                     
                    }

                    lastMousePos = Mouse::screenPos;
                    break;

                case sf::Event::MouseWheelScrolled:
                    const sf::Vector2f worldPosBeforeZoom = window.mapPixelToCoords(lastMousePos, view);

                    if (event.mouseWheelScroll.delta > 0 && Mouse::zoomFactor < maxZoom)
                        view.zoom(1 - zoomStrength);
                    else if (event.mouseWheelScroll.delta < 0 && Mouse::zoomFactor > minZoom)
                        view.zoom(1 + zoomStrength);

                    Mouse::updateZoomFactor(window, view);
                    if (Mouse::zoomFactor > maxZoom)
                        view.zoom(Mouse::zoomFactor / maxZoom);
                    else if (Mouse::zoomFactor < minZoom)
                        view.zoom(Mouse::zoomFactor / minZoom);
                    Mouse::updateZoomFactor(window, view);

                    const sf::Vector2f worldPosAfterZoom = window.mapPixelToCoords(lastMousePos, view);
                    view.move(worldPosBeforeZoom - worldPosAfterZoom);
                    break;
            }
        }

        // Logic
        Clock::updateClock();
        Debug::updatePausedLabel();
        if (Debug::menu) Debug::updateMenu();

        while (Clock::gameUpdate())
            if (!isPaused) Cell::updateMap();

        // Render
        window.clear();

        Cell::render(window);

        // Fixed view
        window.setView(window.getDefaultView());
        if (isPaused && Debug::pausedLabelVisible) Debug::renderPausedLabel(window);
        if (Debug::menu) Debug::renderMenu(window);
        window.setView(view);

        window.display();
    }

    return 0;
}