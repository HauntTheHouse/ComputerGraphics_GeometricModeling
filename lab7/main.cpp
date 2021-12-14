#include <SFML/Graphics.hpp>
#include <Menu.h>
#include "DragonCurve.h"

int main()
{
    const auto WINDOW_SIZE = sf::Vector2i(800, 600);
    const auto MENU_SIZE = sf::Vector2i(200, WINDOW_SIZE.y);
    const auto GRID_SIZE = sf::Vector2i(WINDOW_SIZE.x - MENU_SIZE.x, WINDOW_SIZE.y);

    const auto GRID_CENTER = sf::Vector2i(MENU_SIZE.x + GRID_SIZE.x/2.0f, GRID_SIZE.y/2.0f);

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Lab3", sf::Style::Close);
    sf::View view(sf::FloatRect(-GRID_CENTER.x, -GRID_CENTER.y, WINDOW_SIZE.x, WINDOW_SIZE.y));
    window.setView(view);

    Menu menu(window, {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

    const auto parametersPanel = CustomPanel::create("Parameters", {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

    float unit, iterNum;

    parametersPanel->addSlider("Unit: ", &unit,  0.1f, 30.1f, 0.1f);
    parametersPanel->addSlider("IterNum: ", &iterNum,  0.0f, 30.0f, 1.0f);

    std::vector<std::shared_ptr<CustomPanel>> panels{ parametersPanel };
    menu.addTabs(panels);

    DragonCurve dragonCurve(window, GRID_SIZE, unit);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            menu.handleEvent(event);
            for (const auto& panel : panels)
                panel->updateChangeableValues();
        }

        window.clear(sf::Color(255, 255, 255, 255));

        dragonCurve.drawAxis(sf::Color::Black);
        dragonCurve.drawDragonCurve(static_cast<size_t>(iterNum));
        menu.draw();
        window.display();
    }
    return 0;
}
