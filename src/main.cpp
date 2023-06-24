#include "camera.hpp"
#include "cell.hpp"
#include "clock.hpp"
#include "config.hpp"
#include "debug.hpp"
#include "mouse.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    sf::VideoMode videoMode = sf::VideoMode(width, height);
    if (fullscreen) videoMode = sf::VideoMode::getFullscreenModes()[0];

    sf::RenderWindow window(videoMode, windowName);
    window.setFramerateLimit(fpsLimit);
    window.setVerticalSyncEnabled(vSync);
    window.setKeyRepeatEnabled(false);

    Camera::init(window);
    Debug::init();
    Mouse::updatePositions(window);

    bool isPaused = true;

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
                            Mouse::mousePress(window);
                            break;
                    }
                    break;

                case sf::Event::MouseButtonReleased:
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            if (!Mouse::mouseDragged())
                                Cell::toggleCell(Mouse::gridPos, nullptr);
                            break;
                    }
                    break;

                case sf::Event::MouseMoved:
                    Mouse::updatePositions(window);

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        Camera::move(-sf::Vector2f(Mouse::screenPos - Mouse::prevScreenPos));
                    break;

                case sf::Event::MouseWheelScrolled:
                    Camera::zoom(event.mouseWheelScroll.delta < 0, window);
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
        Camera::setView(window);

        window.display();
    }

    return 0;
}