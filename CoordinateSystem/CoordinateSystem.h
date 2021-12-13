#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <SFML/Graphics.hpp>

class CoordinateSystem
{
public:
    CoordinateSystem(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit);
    void drawGrid(const sf::Color& aAxisColor = sf::Color(0, 0, 0, 255), const sf::Color& aGridColor = sf::Color(180, 180, 180, 255), const sf::Transform& aTransform = sf::Transform::Identity);

    static const float PI;

protected:
    static void addLine(sf::VertexArray &aVertexArray, const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor);

    sf::RenderWindow& mRenderWindow;
    sf::Vector2f mSize;
    float& mUnit;
};


#endif //COORDINATESYSTEM_H
