#include "cell.hpp"
#include "cellMap.hpp"
#include "config.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

int main()
{
    sf::RenderWindow window { sf::VideoMode(WIDTH, HEIGHT), NAME };
    window.setFramerateLimit(FPSLIMIT);
    window.setVerticalSyncEnabled(VSYNC);

    CellMap cellMap;

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

        // Render
        window.clear();
        for (auto &pair : cellMap) pair.second.render(window);
        window.display();
    }

    return 0;
}