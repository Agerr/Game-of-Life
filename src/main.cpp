#include "cell.hpp"
#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window { sf::VideoMode(WIDTH, HEIGHT), NAME };
    window.setFramerateLimit(FPSLIMIT);
    window.setVerticalSyncEnabled(VSYNC);

    const sf::Time updateFrequency = sf::seconds(1.0f / UPS);
    sf::Clock clock;
    sf::Time timeSinceUpdate = sf::Time::Zero;
    
    CellMap cellMap;
    bool paused = true;

    while (window.isOpen())
    {
        // Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed                  :   window.close(); break;
                
                // Keyboard events
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape       :   window.close(); break;
                        case sf::Keyboard::Space        :   paused ? paused = false : paused = true;
                    }
                    break;

                // Mouse events
                case sf::Event::MouseButtonPressed:
                {
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            const int pressed_col = event.mouseButton.x / SIZE;
                            const int pressed_row = event.mouseButton.y / SIZE;
                            Cell::toggleCell(pressed_col, pressed_row, cellMap);
                            break;
                    }
                    break;
                }
            }
        }

        // Logic
        timeSinceUpdate += clock.restart();
        while (timeSinceUpdate > updateFrequency)
        {
            timeSinceUpdate -= updateFrequency;

            if (!paused) Cell::updateMap(cellMap);
        }

        // Render
        window.clear();
        for (auto &pair : cellMap) pair.second.render(window);
        window.display();
    }

    return 0;
}