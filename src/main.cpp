#include <SFML/Graphics.hpp>

int main()
{
    /*That's window properties of my game*/
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Cyber pet game");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}