#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include <Menu.h>
#include "Torus.h"
#include "../lab3_4/BezierCurve2.h"

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
    float numMainSegments, numTubeSegments, r, R;
    float translateX, translateY, translateZ;

    parametersPanel->addSlider("Unit: ", &unit,  10.0f, 30.0f, 1.0f);
    parametersPanel->addSlider("Alpha: ", &alpha,-90.0f, 90.0f, 1.0f);
    parametersPanel->addSlider("NumMainSegm.: ", &numMainSegments,  2.0f, 100.0f, 1.0f);
    parametersPanel->addSlider("NumTubeSegm.: ", &numTubeSegments,  2.0f, 80.0f, 1.0f);
    parametersPanel->addSlider("R: ", &R,  1.0f, 19.0f, 0.1f);
    parametersPanel->addSlider("r: ", &r,  1.0f, 5.0f, 0.1f);
    parametersPanel->addSlider("TranslateX: ", &translateX, -10.0f, 10.0f, 0.5f);
    parametersPanel->addSlider("TranslateY: ", &translateY, -10.0f, 10.0f, 0.5f);
    parametersPanel->addSlider("TranslateZ: ", &translateZ, -10.0f, 10.0f, 0.5f);

    std::vector<std::shared_ptr<CustomPanel>> panels{ parametersPanel };
    menu.addTabs(panels);

    auto vertexArray = BezierCurve2::getVertexArray({
            {-4.0f,-2.5f}, {-8.0f,-2.0f}, {-8.0f, 0.0f},
            {-8.0f, 0.0f}, {-7.0f, 3.0f}, {-4.0f, 3.0f},
            {-4.0f, 3.0f}, {-2.0f, 3.0f}, {-1.5f, 5.0f},
            {-1.5f, 5.0f}, { 0.0f,11.0f}, {0.0f, 5.0f},
            { 0.0f, 5.0f}, { 0.0f, 2.5f}, {2.0f, 2.0f},
            { 2.0f, 2.0f}, { 5.0f, 5.0f}, {3.0f, 1.5f},
            { 3.0f, 1.5f}, {3.75f,1.25f}, {4.5f, 1.0f},
            { 4.5f, 1.0f}, { 4.5f, 4.5f}, {8.0f, 5.5f},
            { 8.0f, 5.5f}, { 4.0f, 0.0f}, {9.0f,-6.0f},
            { 9.0f,-6.0f}, { 5.0f,-4.0f}, {4.5f,-1.0f},
            { 4.5f,-1.0f}, { 4.0f,-1.25f},{3.0f,-1.5f},
            { 3.0f,-1.5f}, { 4.0f,-7.0f}, {1.5f,-2.0f},
            { 1.5f,-2.0f}, {0.75f,-2.5f}, {0.0f,-2.5f},
            { 0.0f,-2.5f}, {-0.5f,-4.0f}, {1.0f,-8.0f},
            { 1.0f,-8.0f}, {-2.5f,-4.0f}, {-2.0f,-2.5f},
            {-2.0f,-2.5f}, {-5.0f,-11.0f},{-4.0f,-2.5f},
    }, 15);

    Torus torus(window, GRID_SIZE, unit, vertexArray);

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

        torus.drawGrid(sf::Color::Black, sf::Color(225,225,225,255));
        torus.drawTorus(R, r, static_cast<int>(numMainSegments), static_cast<int>(numTubeSegments), alpha, translate);
        menu.draw();
        window.display();
    }
    return 0;
}
