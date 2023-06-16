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
    
    sf::View view = window.getView();

    Debug::init();

    CellMap cellMap;

    bool isPaused = true;
    bool leftPressed = false;
    sf::Vector2i lastMousePos;
    sf::Vector2i draggingOffset;

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
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            leftPressed = true;
                            lastMousePos = sf::Mouse::getPosition(window);

                            const sf::Vector2f worldPos = window.mapPixelToCoords(lastMousePos);
                            const int pressed_col = int(worldPos.x / size) - (worldPos.x < 0 ? 1 : 0);
                            const int pressed_row = int(worldPos.y / size) - (worldPos.y < 0 ? 1 : 0);
                            Cell::toggleCell(pressed_col, pressed_row, cellMap);
                            break;
                    }
                    break;

                case sf::Event::MouseButtonReleased:
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            leftPressed = false;
                            break;
                    }
                    break;

                case sf::Event::MouseMoved:
                    if (leftPressed)
                    {
                        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                        draggingOffset = currentMousePos - lastMousePos;

                        view.move(-draggingOffset.x, -draggingOffset.y);
                        window.setView(view);

                        lastMousePos = currentMousePos;
                    }

                    Debug::updateCoords(window);
                    break;
            }
        }

        // Logic
        Clock::updateClock();
        Debug::updatePausedLabel();

        while (Clock::gameUpdate())
        {
            if (!isPaused) Cell::updateMap(cellMap);
        }

        // Render
        window.clear();

        Cell::render(window, cellMap);
        if (isPaused && Debug::pausedLabelVisible) Debug::renderPausedLabel(window);
        if (Debug::menu) Debug::renderMenu(window);

        window.display();
    }

    return 0;
}