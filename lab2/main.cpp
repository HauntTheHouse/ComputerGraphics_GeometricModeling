#include <SFML/Graphics.hpp>
#include <cmath>

#include <Menu.h>
#include "PerseusSpiric.h"

int main()
{
    const auto WINDOW_SIZE = sf::Vector2i(800, 600);
    const auto MENU_SIZE = sf::Vector2i(200, WINDOW_SIZE.y);
    const auto GRID_SIZE = sf::Vector2i(WINDOW_SIZE.x - MENU_SIZE.x, WINDOW_SIZE.y);

    const auto GRID_CENTER = sf::Vector2i(MENU_SIZE.x + GRID_SIZE.x/2.0f, GRID_SIZE.y/2.0f);

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Lab1", sf::Style::Close);
    auto view = sf::View(sf::FloatRect(-GRID_CENTER.x, -GRID_CENTER.y, WINDOW_SIZE.x, WINDOW_SIZE.y));
    window.setView(view);

    Menu menu(window, {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

    const auto parametersPanel = CustomPanel::create("Parameters", {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

    float unit;
    parametersPanel->addSlider("Unit: ", &unit, 10.0f, 30.0f, 1.0f);

    float parameters[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    parametersPanel->addSlider("PointsNum: ", parameters + 0, 4.0f, 150.0f, 1.0f);
    parametersPanel->addSlider("a: ", parameters + 1, 0.0f, 10.0f, 0.2f);
    parametersPanel->addSlider("Theta: ", parameters + 5, 0.0f, 360.0f, 0.2f);
    parametersPanel->addLabel("CurveLength: ", parameters + 2);
    parametersPanel->addLabel("CurveArea: ", parameters + 3);
    parametersPanel->addLabel("CurvatureRadius: ", parameters + 4);

    const auto euclideanPanel = CustomPanel::create("Euclidean", {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

    float translateX, translateY;
    euclideanPanel->addSlider("TranslateX: ", &translateX, -10.0f, 10.0f, 0.5f);
    euclideanPanel->addSlider("TranslateY: ", &translateY, -10.0f, 10.0f, 0.5f);

    float rotateDegree;
    euclideanPanel->addSlider("RotateDegree: ", &rotateDegree, -180.0f, 180.0f, 1.0f);

    bool hasSymmetryX, hasSymmetryY;
    euclideanPanel->addCheckbox("SymmetryX", &hasSymmetryX);
    euclideanPanel->addCheckbox("SymmetryY", &hasSymmetryY);

    std::vector<std::shared_ptr<CustomPanel>> panels{ parametersPanel, euclideanPanel };
    menu.addTabs(panels);

    PerseusSpiric spiric(window, GRID_SIZE, unit);

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

        sf::Transform translate(
                1.0f, 0.0f, unit * translateX,
                0.0f, 1.0f, unit * translateY,
                0.0f, 0.0f, 1.0f
        );

        const auto radian = rotateDegree * PerseusSpiric::PI / 180.0f;
        sf::Transform rotate(
                cosf(radian), -sinf(radian), 0.0f,
                sinf(radian),  cosf(radian), 0.0f,
                0.0f, 0.0f, 1.0f
        );

        const auto reflectionX = hasSymmetryX ? -1.0f : 1.0f;
        const auto reflectionY = hasSymmetryY ? -1.0f : 1.0f;
        sf::Transform reflection(
                reflectionY, 0.0f, 0.0f,
                0.0f, reflectionX, 0.0f,
                0.0f, 0.0f, 1.0f
        );

        const auto transform = reflection * translate * rotate;

        spiric.drawGrid(sf::Color(130, 130, 130), sf::Color(240, 240, 240));
        spiric.drawGrid(sf::Color(0,0,0,255), sf::Color(180,180,180,255), transform);
        spiric.drawPerseusSpiric(parameters, transform);

        menu.draw();
        window.display();
    }
    return 0;
}