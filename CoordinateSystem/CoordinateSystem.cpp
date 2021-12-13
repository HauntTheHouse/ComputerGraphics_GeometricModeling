#include "CoordinateSystem.h"

const float CoordinateSystem::PI = 3.14159265358979323846f;

CoordinateSystem::CoordinateSystem(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit)
    : mRenderWindow(aRenderWindow)
    , mSize(aSize)
    , mUnit(aUnit)
{
}

void CoordinateSystem::drawGrid(const sf::Color& aAxisColor, const sf::Color& aGridColor, const sf::Transform& aTransform)
{
    sf::VertexArray lines(sf::PrimitiveType::Lines);

/* Add vertical lines */
    for (float i = mUnit; i < mSize.x/2.0f; i+=mUnit)
    {
        addLine(lines,
                aTransform * sf::Vector2f(i, -mSize.y/2.0f),
                aTransform * sf::Vector2f(i, mSize.y/2.0f),
                aGridColor);
    }
    for (float i = mUnit; i < mSize.x/2.0f; i+=mUnit)
    {
        addLine(lines,
                aTransform * sf::Vector2f(-i, -mSize.y/2.0f),
                aTransform * sf::Vector2f(-i, mSize.y/2.0f),
                aGridColor);
    }

/* Add horizontal lines */
    for (float i = mUnit; i < mSize.y/2.0f; i+=mUnit)
    {
        addLine(lines,
                aTransform * sf::Vector2f(-mSize.x / 2.0f, i),
                aTransform * sf::Vector2f(mSize.x / 2.0f, i),
                aGridColor);
    }
    for (float i = mUnit; i < mSize.y/2.0f; i+=mUnit)
    {
        addLine(lines,
                aTransform * sf::Vector2f(-mSize.x / 2.0f, -i),
                aTransform * sf::Vector2f(mSize.x / 2.0f, -i),
                aGridColor);
    }

/* Add main axis */

    addLine(lines,
            aTransform * sf::Vector2f(0.0f, -mSize.y/2.0f),
            aTransform * sf::Vector2f(0.0f, mSize.y/2.0f),
            aAxisColor);
    addLine(lines,
            aTransform * sf::Vector2f(-mSize.x / 2.0f, 0.0f),
            aTransform * sf::Vector2f(mSize.x / 2.0f, 0.0f),
            aAxisColor);

    mRenderWindow.draw(lines);
}

void CoordinateSystem::addLine(sf::VertexArray &aVertexArray, const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor)
{
    aVertexArray.append(sf::Vertex(aFrom, aColor));
    aVertexArray.append(sf::Vertex(aTo, aColor));
}
