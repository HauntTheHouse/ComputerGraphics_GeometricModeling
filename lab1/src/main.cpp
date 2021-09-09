#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <iostream>

const auto WINDOW_WIDTH = 800;
const auto WINDOW_HEIGHT = 600;

const auto SCENE_WIDTH = 600;
const auto SCENE_HEIGHT = 600;

const auto GUI_WIDTH = 200;
const auto GUI_HEIGHT = 600;

void drawAxis(sf::RenderWindow& window, float unit, sf::Color color)
{
    sf::VertexArray lines{sf::PrimitiveType::Lines};
    sf::Vector2f center(SCENE_WIDTH/2.0f + GUI_WIDTH, SCENE_HEIGHT/2.0f);

    lines.append(sf::Vertex(sf::Vector2f(center.x, 0.0f), color));
    lines.append(sf::Vertex(sf::Vector2f(center.x, SCENE_HEIGHT), color));
    for (float i = unit; i < SCENE_WIDTH/2.0f; i+=unit)
    {
        lines.append(sf::Vertex(sf::Vector2f(center.x + i, 0.0f), sf::Color(180, 180, 180, 255)));
        lines.append(sf::Vertex(sf::Vector2f(center.x + i, WINDOW_HEIGHT), sf::Color(180, 180, 180, 255)));
    }
    for (float i = unit; i < SCENE_WIDTH/2.0f; i+=unit)
    {
        lines.append(sf::Vertex(sf::Vector2f(center.x - i, 0.0f), sf::Color(180, 180, 180, 255)));
        lines.append(sf::Vertex(sf::Vector2f(center.x - i, WINDOW_HEIGHT), sf::Color(180, 180, 180, 255)));
    }

    lines.append(sf::Vertex(sf::Vector2f(GUI_WIDTH, center.y), color));
    lines.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH, center.y), color));
    for (float i = unit; i < SCENE_HEIGHT/2.0f; i+=unit)
    {
        lines.append(sf::Vertex(sf::Vector2f(GUI_WIDTH, center.y + i), sf::Color(180, 180, 180, 255)));
        lines.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH, center.y + i), sf::Color(180, 180, 180, 255)));
    }
    for (float i = unit; i < SCENE_HEIGHT/2.0f; i+=unit)
    {
        lines.append(sf::Vertex(sf::Vector2f(GUI_WIDTH, center.y - i), sf::Color(180, 180, 180, 255)));
        lines.append(sf::Vertex(sf::Vector2f(WINDOW_WIDTH, center.y - i), sf::Color(180, 180, 180, 255)));
    }

    window.draw(lines);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Lab1");
    tgui::Gui gui{window};

    tgui::Slider::Ptr slider = tgui::Slider::create(10, 30);
    slider->setPosition(10, 10);
    slider->setSize(180, 10);
    slider->setValue(20.0f);
    slider->setTextSize(10);
    slider->setChangeValueOnScroll(true);
    gui.add(slider);
    
    sf::Font font{};
    font.loadFromFile("fonts/FreeSerif.ttf");

    sf::Text text{"Unit: ", font, 14};
    text.setPosition(tgui::Vector2f(45.0f, 30.0f));
    text.setFillColor(sf::Color(0, 0, 0));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            gui.handleEvent(event);
        }

        window.clear(sf::Color(255, 255, 255, 255));

        drawAxis(window, slider->getValue(), sf::Color());
        text.setString("Unit: " + std::to_string(slider->getValue()));

        gui.draw();
        window.draw(text);

        window.display();
    }
    return 0;
}