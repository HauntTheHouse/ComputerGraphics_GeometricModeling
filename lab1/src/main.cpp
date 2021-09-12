#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "CoordinateSystem.h"

int main()
{
    const auto WINDOW_WIDTH = 800;
    const auto WINDOW_HEIGHT = 600;

    const auto MENU_WIDTH = 200;
    const auto MENU_HEIGHT = 600;

    const auto GRID_WIDTH = WINDOW_WIDTH - MENU_WIDTH;
    const auto GRID_HEIGHT = WINDOW_HEIGHT;

    const auto GRID_CENTER = sf::Vector2f(MENU_WIDTH + GRID_WIDTH/2.0f, GRID_HEIGHT/2.0f);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lab1", sf::Style::Close);

    Menu menu(window, MENU_WIDTH, MENU_HEIGHT);
    CoordinateSystem coordinateSystem(window, GRID_CENTER, GRID_WIDTH, GRID_HEIGHT);

    float unit;
    menu.addSlider("Unit: ", &unit, 10.0f, 30.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            menu.handleEvent(event);
        }

        window.clear(sf::Color(255, 255, 255, 255));

        menu.draw();
        coordinateSystem.drawGrid(unit);

        window.display();
    }
    return 0;
}