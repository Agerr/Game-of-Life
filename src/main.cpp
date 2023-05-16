#include "cell.hpp"
#include "cellMap.hpp"
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

    // Game clock
    sf::Clock clock;

    const sf::Time updateFrequency = sf::seconds(1.0f / ups);
    sf::Time timeSinceUpdate = sf::Time::Zero;

    const sf::Time blinkFrequency = sf::seconds(1.0f / blinksPerSecond);
    sf::Time timeSinceBlink = sf::Time::Zero;
    bool labelVisible = true;

    Debug debug;

    CellMap cellMap;
    bool paused = true;

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
                        case sf::Keyboard::F1           :   debug.toggleMenu();     break;
                        case sf::Keyboard::Space        :   paused = !paused;       break;
                    }
                    break;

                // Mouse events
                case sf::Event::MouseButtonPressed:
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            const int pressed_col = event.mouseButton.x / size;
                            const int pressed_row = event.mouseButton.y / size;
                            Cell::toggleCell(pressed_col, pressed_row, cellMap);
                            break;
                    }
                    break;


                case sf::Event::MouseMoved:
                    debug.updateCoords(window);
                    break;
            }
        }

        // Logic
        const sf::Time timeElapsed = clock.restart();
        // timeSinceBlink += timeElapsed;
        timeSinceUpdate += timeElapsed;

        // if (timeSinceBlink >= blinkFrequency)
        // {
        //     timeSinceBlink = sf::Time::Zero;
        //     labelVisible = !labelVisible;
        // }

        while (timeSinceUpdate > updateFrequency)
        {
            timeSinceUpdate -= updateFrequency;

            if (!paused) Cell::updateMap(cellMap);
        }

        // Render
        window.clear();

        for (auto &pair : cellMap) pair.second.render(window);
        // if (paused && labelVisible) window.draw(pausedLabel);
        if (debug.menu) debug.renderMenu(window);

        window.display();
    }

    return 0;
}