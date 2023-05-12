#include <SFML/Graphics.hpp>

int main()
{
    // Window
    sf::RenderWindow window { sf::VideoMode(1280, 720), "_test_" };
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // While the window is open
    while (window.isOpen())
    {
        // Events
        sf::Event event;
        while (window.pollEvent(event))
        {
           if (event.type == sf::Event::Closed) window.close();
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        // Render
        window.clear();
        window.display();
    }

    return 0;
}