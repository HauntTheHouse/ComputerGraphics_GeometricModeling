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
    float unit;
    menu.addSlider("Unit: ", &unit, 12.0f, 26.0f, 1.0f);

    float pointsNum;
    menu.addSlider("PointsNum: ", &pointsNum, 6.0f, 34.0f, 1.0f);

    float parameters[5];
    menu.addSlider("Parameter1: ", parameters + 0, 1.0f, 5.0f, 0.5f);
    menu.addSlider("Parameter2: ", parameters + 1,-9.0f,-5.0f, 0.5f);
    menu.addSlider("Parameter3: ", parameters + 2, 0.5f, 2.5f, 0.25f);
    menu.addSlider("Parameter4: ", parameters + 3, 2.0f, 6.0f, 0.5f);
    menu.addSlider("Parameter5: ", parameters + 4, 0.0f, 6.0f, 0.5f);

    CoordinateSystem coordinateSystem(window, GRID_CENTER, GRID_WIDTH, GRID_HEIGHT, unit, pointsNum);

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
        coordinateSystem.drawGrid();
        coordinateSystem.drawFigure(parameters);

        window.display();
    }
    return 0;
}