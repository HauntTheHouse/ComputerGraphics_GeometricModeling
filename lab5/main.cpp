#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include <Menu.h>
#include "CabinetProjection.h"

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

    float unit, alpha;
    float translateX, translateY, translateZ;

    parametersPanel->addSlider("Unit: ",  &unit,  10.0f, 30.0f, 1.0f);
    parametersPanel->addSlider("Alpha: ", &alpha,-90.0f, 90.0f, 1.0f);
    parametersPanel->addSlider("TranslateX: ", &translateX, -10.0f, 10.0f, 0.5f);
    parametersPanel->addSlider("TranslateY: ", &translateY, -10.0f, 10.0f, 0.5f);
    parametersPanel->addSlider("TranslateZ: ", &translateZ, -10.0f, 10.0f, 0.5f);

    CabinetProjection cavalierProjection(window, GRID_SIZE, unit);

    std::vector<std::shared_ptr<CustomPanel>> panels{ parametersPanel };
    menu.addTabs(panels);

    std::vector<glm::vec3> cube {
        {-1.0f,-1.0f,-1.0f}, {-1.0f, 1.0f,-1.0f},
        {-1.0f, 1.0f,-1.0f}, { 1.0f, 1.0f,-1.0f},
        { 1.0f, 1.0f,-1.0f}, { 1.0f,-1.0f,-1.0f},
        { 1.0f,-1.0f,-1.0f}, {-1.0f,-1.0f,-1.0f},

        {-1.0f,-1.0f,-1.0f}, {-1.0f,-1.0f, 1.0f},
        {-1.0f,-1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f,-1.0f},

        { 1.0f,-1.0f,-1.0f}, { 1.0f,-1.0f, 1.0f},
        { 1.0f,-1.0f, 1.0f}, { 1.0f, 1.0f, 1.0f},
        { 1.0f, 1.0f, 1.0f}, { 1.0f, 1.0f,-1.0f},

        {-1.0f, 1.0f, 1.0f}, { 1.0f, 1.0f, 1.0f},
        {-1.0f,-1.0f, 1.0f}, { 1.0f,-1.0f, 1.0f}
    };

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

        glm::mat4 translate(
            1.0f,              0.0f,              0.0f,              0.0f,
            0.0f,              1.0f,              0.0f,              0.0f,
            0.0f,              0.0f,              1.0f,              0.0f,
            unit * translateX, unit * translateY, unit * translateZ, 1.0f
        );

        cavalierProjection.drawGrid(sf::Color::Blue, sf::Color(255,225,225,225));
        cavalierProjection.drawCavalierProjection(cube, alpha, translate);
        menu.draw();
        window.display();
    }
    return 0;
}