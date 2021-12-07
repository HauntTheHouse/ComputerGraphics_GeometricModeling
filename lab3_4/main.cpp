#include <SFML/Graphics.hpp>
#include <cmath>

#include <Menu.h>
#include "BezierCurve2.h"

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
    const auto euclideanPanel = CustomPanel::create("Euclidean", {0, 0}, {MENU_SIZE.x, MENU_SIZE.y});

    float unit, numLinesPerCurve;
    bool drawContour;
    sf::Vector2f effectorP2;

    parametersPanel->addSlider("Unit: ", &unit, 10.0f, 30.0f, 1.0f);
    parametersPanel->addSlider("Lines per curve: ", &numLinesPerCurve, 2.0f, 28.0f, 1.0f);
    parametersPanel->addCheckbox("Draw polygonal", &drawContour);
    parametersPanel->addSlider("Effector p2.x: ", &effectorP2.x,  -11.5f, -4.5f, 0.1f);
    parametersPanel->addSlider("Effector p2.y: ", &effectorP2.y, 0.5f, 5.5f, 0.1f);

    float translateX, translateY;
    float rotateDegree;
    bool hasSymmetryX, hasSymmetryY;

    euclideanPanel->addSlider("TranslateX: ", &translateX, -10.0f, 10.0f, 0.5f);
    euclideanPanel->addSlider("TranslateY: ", &translateY, -10.0f, 10.0f, 0.5f);
    euclideanPanel->addSlider("RotateDegree: ", &rotateDegree, -180.0f, 180.0f, 1.0f);
    euclideanPanel->addCheckbox("SymmetryX", &hasSymmetryX);
    euclideanPanel->addCheckbox("SymmetryY", &hasSymmetryY);

    std::vector<std::shared_ptr<CustomPanel>> panels{ parametersPanel, euclideanPanel };
    menu.addTabs(panels);

    BezierCurve2 bezierCurve2(window, GRID_SIZE, unit);

    sf::Vector2f fixed1(-8.0f, 0.0f);
    sf::Vector2f p2_1(-8.0f, -2.0f);

    sf::Vector2f fixed2(-4.0f, 3.0f);
    sf::Vector2f p2_2(-2.0f, 3.0f);

    sf::Vector2f fixed3(-1.5f, 5.0f);
    sf::Vector2f p2_3(0.0f, 11.0f);

    sf::Vector2f fixed4(0.0f, 5.0f);
    sf::Vector2f p2_4(0.0f, 2.5f);

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

        const auto radian = rotateDegree * CoordinateSystem::PI / 180.0f;
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

        bezierCurve2.drawGrid(sf::Color(130, 130, 130), sf::Color(240, 240, 240));
        bezierCurve2.drawGrid(sf::Color(0,0,0,255), sf::Color(180,180,180,255), transform);

        p2_1.x = (fixed1.x - effectorP2.x) * (p2_1.y - effectorP2.y) / (fixed1.y - effectorP2.y) + effectorP2.x;
        p2_2.y = (p2_2.x - effectorP2.x) * (fixed2.y - effectorP2.y) / (fixed2.x - effectorP2.x) + effectorP2.y;
        p2_3.x = (fixed3.x - p2_2.x) * (p2_3.y - p2_2.y) / (fixed3.y - p2_2.y) + p2_2.x;
        p2_4.x = (fixed4.x - p2_3.x) * (p2_4.y - p2_3.y) / (fixed4.y - p2_3.y) + p2_3.x;

        bezierCurve2.drawBezierCurve2({
            {-4.0f,-2.5f}, p2_1,          fixed1,
            fixed1,        effectorP2,    fixed2,
            fixed2,        p2_2,          fixed3,
            fixed3,        p2_3,          fixed4,
            fixed4,        p2_4,          {2.0f, 2.0f},
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
        },
        static_cast<int>(numLinesPerCurve),
        drawContour,
        transform);

        menu.draw();
        window.display();
    }
    return 0;
}