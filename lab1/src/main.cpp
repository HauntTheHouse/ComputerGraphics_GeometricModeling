#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "CoordinateSystem.h"
#include <cmath>
#include <iostream>
int main()
{
    const auto WINDOW_SIZE = sf::Vector2i(800, 800);
    const auto MENU_SIZE = sf::Vector2i(200, WINDOW_SIZE.y);
    const auto GRID_SIZE = sf::Vector2i(WINDOW_SIZE.x - MENU_SIZE.x, WINDOW_SIZE.y);

    const auto GRID_CENTER = sf::Vector2i(MENU_SIZE.x + GRID_SIZE.x/2.0f, GRID_SIZE.y/2.0f);

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Lab1", sf::Style::Close);
    auto view = sf::View(sf::FloatRect(-GRID_CENTER.x, -GRID_CENTER.y, WINDOW_SIZE.x, WINDOW_SIZE.y));
    window.setView(view);

    Menu menu(window, {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

    const auto linearPanel = CustomPanel::create("Linear", {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

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

    const auto affinePanel = CustomPanel::create("Affine", {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

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

    sf::Vector2f r0;
    affinePanel->addSlider("r0.x: ", &r0.x, -10.0f, 10.0f, 0.1f);
    affinePanel->addSlider("r0.y: ",   &r0.y, -10.0f, 10.0f, 0.1f);

    sf::Vector2f angleR;
    affinePanel->addKnob("rx", &angleR.x, 270.0f);
    affinePanel->addKnob("ry", &angleR.y, 180.0f);

    const auto projectivePanel = CustomPanel::create("Project.", {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

    bool applyProjective;
    projectivePanel->addCheckbox("Apply projective", &applyProjective);

    sf::Vector3f w;
    projectivePanel->addSlider("w0: ", &w.z, 0.0f, 2000.0f, 0.1f);
    projectivePanel->addSlider("wx: ", &w.x, 0.0f, 2.0f, 0.1f);
    projectivePanel->addSlider("wy: ", &w.y, 0.0f, 2.0f, 0.1f);

    sf::Vector2f rCoef;
    projectivePanel->addSlider("rx coefficient: ", &rCoef.x, -1000.0f, 2000.0f, 0.1f);
    projectivePanel->addSlider("ry coefficient: ", &rCoef.y, -1000.0f, 2000.0f, 0.1f);

    std::vector<std::shared_ptr<CustomPanel>> panels{linearPanel, affinePanel, projectivePanel};
    menu.addTabs(panels);

    CoordinateSystem coordinateSystem(window, GRID_SIZE, unit, pointsNum, angleR, applyProjective, w, r0, rCoef);

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

        const auto transform = reflection * translate * rotate * scale;

        coordinateSystem.drawGrid(sf::Color(0, 0, 0), sf::Color(180, 180, 180), transform);
        coordinateSystem.drawFigure(parameters, transform);

        menu.draw();

        window.display();
    }
    return 0;
}