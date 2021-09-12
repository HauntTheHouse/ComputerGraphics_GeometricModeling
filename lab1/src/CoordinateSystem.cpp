#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(sf::RenderWindow& aRenderWindow, const sf::Vector2f& aCenterOfGrid, unsigned int aWidth, unsigned int aHeight)
    : mRenderWindow(aRenderWindow)
    , mCenterOfGrid(aCenterOfGrid)
    , mWidth(aWidth)
    , mHeight(aHeight)
{
}

void CoordinateSystem::drawGrid(float aUnit)
{
    sf::VertexArray lines{sf::PrimitiveType::Lines};

    for (float i = aUnit; i < mWidth/2.0f; i+=aUnit)
    {
        lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x + i, 0.0f), sf::Color(180, 180, 180, 255)));
        lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x + i, mHeight), sf::Color(180, 180, 180, 255)));
    }
    for (float i = aUnit; i < mWidth/2.0f; i+=aUnit)
    {
        lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x - i, 0.0f), sf::Color(180, 180, 180, 255)));
        lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x - i, mHeight), sf::Color(180, 180, 180, 255)));
    }

    for (float i = aUnit; i < mHeight/2.0f; i+=aUnit)
    {
        lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x - mWidth/2.0f, mCenterOfGrid.y + i), sf::Color(180, 180, 180, 255)));
        lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x + mWidth/2.0f, mCenterOfGrid.y + i), sf::Color(180, 180, 180, 255)));
    }
    for (float i = aUnit; i < mHeight/2.0f; i+=aUnit)
    {
        lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x - mWidth/2.0f, mCenterOfGrid.y - i), sf::Color(180, 180, 180, 255)));
        lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x + mWidth/2.0f, mCenterOfGrid.y - i), sf::Color(180, 180, 180, 255)));
    }

    lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x, 0.0f), sf::Color(0, 0, 0)));
    lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x, mHeight), sf::Color(0, 0, 0)));

    lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x - mWidth/2.0f, mCenterOfGrid.y), sf::Color(0, 0, 0)));
    lines.append(sf::Vertex(sf::Vector2f(mCenterOfGrid.x + mWidth/2.0f, mCenterOfGrid.y), sf::Color(0, 0, 0)));

    mRenderWindow.draw(lines);
}
