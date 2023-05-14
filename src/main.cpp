#include "config.hpp"
#include "cell.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

int main()
{
    // Window
    sf::RenderWindow window { sf::VideoMode(WIDTH, HEIGHT), NAME };
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    const int cols = WIDTH / SIZE;
    const int rows = HEIGHT / SIZE;

    std::vector<Cell> cellVector;

    // While the window is open
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
                            if (pressed_col + 1 > cols || pressed_row + 1 > rows) break;
                            
                            const int x_pos = pressed_col * SIZE;
                            const int y_pos = pressed_row * SIZE;
                            const int index = Cell::atPos(x_pos, y_pos, cellVector);

                            if (index == -1) cellVector.push_back(Cell(x_pos, y_pos, SIZE));
                            else cellVector.erase(cellVector.begin() + index);
                            break;
                    }
                    break;
                }
            }
        }

        // Render
        window.clear();
        for (Cell &cell : cellVector) cell.render(window);
        window.display();
    }

    return 0;
}