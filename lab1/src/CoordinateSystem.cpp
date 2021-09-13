#include "CoordinateSystem.h"
#include <cmath>

const float CoordinateSystem::PI = 3.14159265358979323846f;

CoordinateSystem::CoordinateSystem(sf::RenderWindow& aRenderWindow, const sf::Vector2f& aCenterOfGrid, unsigned int aWidth, unsigned int aHeight, float& aUnit, float& aPointsNum)
    : mRenderWindow(aRenderWindow)
    , mCenterOfGrid(aCenterOfGrid)
    , mWidth(aWidth)
    , mHeight(aHeight)
    , mUnit(aUnit)
    , mPointsNum(aPointsNum)
{
}

void CoordinateSystem::drawGrid()
{
    sf::VertexArray lines(sf::PrimitiveType::Lines);

    const sf::Color grey(180, 180, 180, 255);
    const sf::Color black(0, 0, 0, 255);

/* Add vertical lines */
    for (float i = mUnit; i < mWidth/2.0f; i+=mUnit)
    {
        addLine(lines,
                sf::Vertex(sf::Vector2f(mCenterOfGrid.x + i, 0.0f), grey),
                sf::Vertex(sf::Vector2f(mCenterOfGrid.x + i, mHeight), grey));
    }
    for (float i = mUnit; i < mWidth/2.0f; i+=mUnit)
    {
        addLine(lines,
                sf::Vertex(sf::Vector2f(mCenterOfGrid.x - i, 0.0f), grey),
                sf::Vertex(sf::Vector2f(mCenterOfGrid.x - i, mHeight), grey));
    }

/* Add horizontal lines */
    for (float i = mUnit; i < mHeight/2.0f; i+=mUnit)
    {
        addLine(lines,
                sf::Vertex(sf::Vector2f(mCenterOfGrid.x - mWidth/2.0f, mCenterOfGrid.y + i), grey),
                sf::Vertex(sf::Vector2f(mCenterOfGrid.x + mWidth/2.0f, mCenterOfGrid.y + i), grey));
    }
    for (float i = mUnit; i < mHeight/2.0f; i+=mUnit)
    {
        addLine(lines,
                sf::Vertex(sf::Vector2f(mCenterOfGrid.x - mWidth/2.0f, mCenterOfGrid.y - i), grey),
                sf::Vertex(sf::Vector2f(mCenterOfGrid.x + mWidth/2.0f, mCenterOfGrid.y - i), grey));
    }

/* Add main axis */
    addLine(lines,
            sf::Vertex(sf::Vector2f(mCenterOfGrid.x, 0.0f), black),
            sf::Vertex(sf::Vector2f(mCenterOfGrid.x, mHeight), black));
    addLine(lines,
            sf::Vertex(sf::Vector2f(mCenterOfGrid.x - mWidth/2.0f, mCenterOfGrid.y), black),
            sf::Vertex(sf::Vector2f(mCenterOfGrid.x + mWidth/2.0f, mCenterOfGrid.y), black));

    mRenderWindow.draw(lines);
}

void CoordinateSystem::drawFigure(const float* aParameters)
{
/* Create central half-circle */
    sf::VertexArray lines(sf::PrimitiveType::Lines);
    const auto color = sf::Color(255, 0, 0);

    const auto centroid1 = mCenterOfGrid;
    const auto r1 = aParameters[0] * mUnit;

    const auto fromAngle1 = -2.0f/3.0f*PI;
    const auto toAngle1   =  2.0f/3.0f*PI;

    addArc(lines, centroid1, r1, fromAngle1, toAngle1, color);

    const auto firstPoint1 = sf::Vector2f(r1 * cosf(fromAngle1) + centroid1.x, r1 * sinf(fromAngle1) + centroid1.y);
    const auto lastPoint1  = sf::Vector2f(r1 * cosf(toAngle1)   + centroid1.x, r1 * sinf(toAngle1)   + centroid1.y);

    const auto upPoint1    = sf::Vector2f(r1 * cosf(-1.0f / 2.0f * M_PI) + centroid1.x, r1 * sinf(-1.0f / 2.0f * M_PI) + centroid1.y);
    const auto downPoint1  = sf::Vector2f(r1 * cosf( 1.0f / 2.0f * M_PI) + centroid1.x, r1 * sinf( 1.0f / 2.0f * M_PI) + centroid1.y);
    const auto rightPoint1 = sf::Vector2f(r1 + centroid1.x, centroid1.y);

/* Create left half-circle */

    const auto centroid2 = mCenterOfGrid + sf::Vector2f(aParameters[1] * mUnit, 0.0f);
    const auto r2 = aParameters[2] * mUnit;

    const auto fromAngle2 = 1.0f/2.0f*PI;
    const auto toAngle2   = 3.0f/2.0f*PI;

    addArc(lines, centroid2, r2, fromAngle2, toAngle2, color);

    const auto firstPoint2 = sf::Vector2f(r2 * cosf(fromAngle2) + centroid2.x, r2 * sinf(fromAngle2) + centroid2.y);
    const auto lastPoint2  = sf::Vector2f(r2 * cosf(toAngle2)   + centroid2.x, r2 * sinf(toAngle2)   + centroid2.y);

/* Bind edges of central and left half-circles */

    addLine(lines, sf::Vertex(firstPoint1, color), sf::Vertex(lastPoint2, color));
    addLine(lines, sf::Vertex(firstPoint2, color), sf::Vertex(lastPoint1, color));

/* Create first up-right circle */

    const auto centroid3 = mCenterOfGrid + sf::Vector2f(aParameters[3] * mUnit, -aParameters[3] * mUnit);
    const auto r3 = 1.5f * mUnit;

    addArc(lines, centroid3, r3, 0.0f, 2.0f*PI, color);

    const auto leftUpPoint3    = sf::Vector2f(r3 * cosf(-3.0f / 4.0f * M_PI) + centroid3.x, r3 * sinf(-3.0f / 4.0f * M_PI) + centroid3.y);
    const auto rightDownPoint3 = sf::Vector2f(r3 * cosf( 1.0f / 4.0f * M_PI) + centroid3.x, r3 * sinf( 1.0f / 4.0f * M_PI) + centroid3.y);

/* Bind edges of central half-circle and first up-right circle */

    addLine(lines, sf::Vertex(leftUpPoint3,    color), sf::Vertex(upPoint1,    color));
    addLine(lines, sf::Vertex(rightDownPoint3, color), sf::Vertex(rightPoint1, color));

/* Create first down-right circle */

    const auto centroid4 = mCenterOfGrid + sf::Vector2f(aParameters[3] * mUnit, aParameters[3] * mUnit);
    const auto r4 = 1.5f * mUnit;

    addArc(lines, centroid4, r4, 0.0f, 2.0f*PI, color);

    const auto rightUpPoint4  = sf::Vector2f(r4 * cosf(-1.0f / 4.0f * M_PI) + centroid4.x, r4 * sinf(-1.0f / 4.0f * M_PI) + centroid4.y);
    const auto leftDownPoint4 = sf::Vector2f(r4 * cosf( 3.0f / 4.0f * M_PI) + centroid4.x, r4 * sinf( 3.0f / 4.0f * M_PI) + centroid4.y);

/* Bind edges of central half-circle and first down-right circle */

    addLine(lines, sf::Vertex(leftDownPoint4, color), sf::Vertex(downPoint1,  color));
    addLine(lines, sf::Vertex(rightUpPoint4,  color), sf::Vertex(rightPoint1, color));

/* Create second up-right circle */

    const auto centroid5 = mCenterOfGrid + sf::Vector2f((aParameters[3] + aParameters[4]) * mUnit, -(aParameters[3] + aParameters[4]) * mUnit);
    const auto r5 = 2.0f * mUnit;

    addArc(lines, centroid5, r5, 0.0f, 2.0f*PI, color);

    const auto leftUpPoint5    = sf::Vector2f(r5 * cosf(-3.0f / 4.0f * M_PI) + centroid5.x, r5 * sinf(-3.0f / 4.0f * M_PI) + centroid5.y);
    const auto rightDownPoint5 = sf::Vector2f(r5 * cosf( 1.0f / 4.0f * M_PI) + centroid5.x, r5 * sinf( 1.0f / 4.0f * M_PI) + centroid5.y);

/* Bind edges of first up-right circle and second up-right circle */

    addLine(lines, sf::Vertex(leftUpPoint5,    color), sf::Vertex(leftUpPoint3,    color));
    addLine(lines, sf::Vertex(rightDownPoint5, color), sf::Vertex(rightDownPoint3, color));

/* Create second down-right circle */

    const auto centroid6 = mCenterOfGrid + sf::Vector2f((aParameters[3] + aParameters[4]) * mUnit, (aParameters[3] + aParameters[4]) * mUnit);
    const auto r6 = 2.0f * mUnit;

    addArc(lines, centroid6, r6, 0.0f, 2.0f*PI, color);

    const auto rightUpPoint6  = sf::Vector2f(r6 * cosf(-1.0f / 4.0f * M_PI) + centroid6.x, r6 * sinf(-1.0f / 4.0f * M_PI) + centroid6.y);
    const auto leftDownPoint6 = sf::Vector2f(r6 * cosf( 3.0f / 4.0f * M_PI) + centroid6.x, r6 * sinf( 3.0f / 4.0f * M_PI) + centroid6.y);

/* Bind edges of first down-right circle and second down-right circle */

    addLine(lines, sf::Vertex(leftDownPoint6, color), sf::Vertex(leftDownPoint4, color));
    addLine(lines, sf::Vertex(rightUpPoint6,  color), sf::Vertex(rightUpPoint4,  color));

    mRenderWindow.draw(lines);
}

void CoordinateSystem::addArc(sf::VertexArray& aVertexArray, const sf::Vector2f& aCenter, float aR, float aFromAngle, float aToAngle, const sf::Color& aColor) const
{
    const auto phi = (aToAngle - aFromAngle) / (mPointsNum - 1);

    for (int i = 0; i < mPointsNum - 1; ++i)
    {
        const auto curPhi = i * phi + aFromAngle;
        const auto from = sf::Vertex(sf::Vector2f(aR * cosf(curPhi + 0.0f) + aCenter.x, aR * sinf(curPhi + 0.0f) + aCenter.y), aColor);
        const auto to   = sf::Vertex(sf::Vector2f(aR * cosf(curPhi + phi ) + aCenter.x, aR * sinf(curPhi + phi ) + aCenter.y), aColor);
        addLine(aVertexArray, from, to);
    }
}

void CoordinateSystem::addLine(sf::VertexArray &aVertexArray, const sf::Vertex &aFrom, const sf::Vertex &aTo)
{
    aVertexArray.append(aFrom);
    aVertexArray.append(aTo);
}

