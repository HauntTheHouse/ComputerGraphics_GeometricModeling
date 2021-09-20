#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "CoordinateSystem.h"
#include <cmath>

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

    const auto pos  = sf::Vector2i(0, 0);
    const auto size = sf::Vector2i(MENU_WIDTH, MENU_HEIGHT);

    Menu menu(window, pos, size);

    const auto linearPanel = CustomPanel::create("Linear", pos, size, 12.0f);

    float unit;
    linearPanel->addSlider("Unit: ", &unit, 12.0f, 26.0f, 1.0f);

    float pointsNum;
    linearPanel->addSlider("PointsNum: ", &pointsNum, 6.0f, 34.0f, 1.0f);

    float parameters[5];
    linearPanel->addSlider("Parameter1: ", parameters + 0, 1.0f, 5.0f, 0.5f);
    linearPanel->addSlider("Parameter2: ", parameters + 1,-9.0f,-5.0f, 0.5f);
    linearPanel->addSlider("Parameter3: ", parameters + 2, 0.5f, 2.5f, 0.25f);
    linearPanel->addSlider("Parameter4: ", parameters + 3, 2.0f, 6.0f, 0.5f);
    linearPanel->addSlider("Parameter5: ", parameters + 4, 0.0f, 6.0f, 0.5f);

    const auto affinePanel = CustomPanel::create("Affine", pos, size, 10.0f);

    float translateX, translateY;
    affinePanel->addSlider("TranslateX: ", &translateX, -10.0f, 10.0f, 0.5f);
    affinePanel->addSlider("TranslateY: ", &translateY, -10.0f, 10.0f, 0.5f);

    float rotateDegree;
    affinePanel->addSlider("RotateDegree: ", &rotateDegree, -180.0f, 180.0f, 1.0f);

    float scaleX, scaleY;
    affinePanel->addSlider("ScaleX: ", &scaleX, 0.0f, 2.0f, 0.1f);
    affinePanel->addSlider("ScaleY: ", &scaleY, 0.0f, 2.0f, 0.1f);

    bool hasSymmetryX, hasSymmetryY;
    affinePanel->addCheckbox("SymmetryX", &hasSymmetryX);
    affinePanel->addCheckbox("SymmetryY", &hasSymmetryY);

    const auto projectivePanel = CustomPanel::create("Project.", pos, size, 10.0f);

    std::vector<std::shared_ptr<CustomPanel>> panels{linearPanel, affinePanel, projectivePanel};
    menu.addTabs(panels);

    CoordinateSystem coordinateSystem(window, GRID_CENTER, GRID_WIDTH, GRID_HEIGHT, unit, pointsNum);

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

        coordinateSystem.drawGrid(sf::Color(130, 130, 130), sf::Color(240, 240, 240));

        sf::Transform centerTransform(
            1.0f, 0.0f, GRID_CENTER.x,
            0.0f, 1.0f, GRID_CENTER.y,
            0.0f, 0.0f, 1.0f
        );

        sf::Transform centerTransformInversed(
                1.0f, 0.0f, -GRID_CENTER.x,
                0.0f, 1.0f, -GRID_CENTER.y,
                0.0f, 0.0f, 1.0f
        );

        sf::Transform translate(
            1.0f, 0.0f, unit * translateX,
            0.0f, 1.0f, unit * translateY,
            0.0f, 0.0f, 1.0f
        );

        const auto radian = rotateDegree * CoordinateSystem::PI / 180.0f;
        sf::Transform rotate(
            cosf(radian), -sinf(radian), 0.0f,
            sinf(radian),  cosf(radian), 0.0f,
            0.0f, 0.0f, 1.0f
        );

        sf::Transform scale(
            scaleX, 0.0f, 0.0f,
            0.0f, scaleY, 0.0f,
            0.0f, 0.0f, 1.0f
        );

        const auto reflectionX = hasSymmetryX ? -1.0f : 1.0f;
        const auto reflectionY = hasSymmetryY ? -1.0f : 1.0f;
        sf::Transform reflection(
            reflectionY, 0.0f, 0.0f,
            0.0f, reflectionX, 0.0f,
            0.0f, 0.0f, 1.0f
        );

        const auto transform = centerTransform * reflection * translate * rotate * scale * centerTransformInversed;

        coordinateSystem.drawGrid(sf::Color(0, 0, 0), sf::Color(180, 180, 180), transform);
        coordinateSystem.drawFigure(parameters, transform);

        menu.draw();

        window.display();
    }
    return 0;
}