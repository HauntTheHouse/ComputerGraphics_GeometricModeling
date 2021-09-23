#include "CoordinateSystem.h"
#include <cmath>
#include <iostream>

namespace
{
    sf::Vector2f normalize(const sf::Vector2f& vec)
    {
        float length = sqrtf((vec.x * vec.x) + (vec.y * vec.y));
        if (length != 0)
            return {vec.x / length, vec.y / length};
        else
            return vec;
    }
}

const float CoordinateSystem::PI = 3.14159265358979323846f;

CoordinateSystem::CoordinateSystem(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit, float& aPointsNum, sf::Vector2f& aAngleR, sf::Vector3f& aW)
    : mRenderWindow(aRenderWindow)
    , mSize(aSize)
    , mUnit(aUnit)
    , mPointsNum(aPointsNum)
    , mAngleR(aAngleR)
    , mW(aW)
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

void CoordinateSystem::drawFigure(const float* aParameters, const sf::Transform& aTransform)
{
/* Create central half-circle */
    sf::VertexArray lines(sf::PrimitiveType::Lines);
    const auto color = sf::Color(255, 0, 0);

    const auto centroid1 = sf::Vector2f(0.0f, 0.0f);
    const auto radius1 = aParameters[0] * mUnit;

    const auto fromAngle1 = -2.0f/3.0f*PI;
    const auto toAngle1   =  2.0f/3.0f*PI;

    addArc(lines, centroid1, radius1, fromAngle1, toAngle1, color, aTransform);

    const auto firstPoint1 = sf::Vector2f(radius1 * cosf(fromAngle1) + centroid1.x, radius1 * sinf(fromAngle1) + centroid1.y);
    const auto lastPoint1  = sf::Vector2f(radius1 * cosf(toAngle1) + centroid1.x, radius1 * sinf(toAngle1) + centroid1.y);

    const auto upPoint1    = sf::Vector2f(radius1 * cosf(-1.0f / 2.0f * PI) + centroid1.x, radius1 * sinf(-1.0f / 2.0f * PI) + centroid1.y);
    const auto downPoint1  = sf::Vector2f(radius1 * cosf(1.0f / 2.0f * PI) + centroid1.x, radius1 * sinf(1.0f / 2.0f * PI) + centroid1.y);
    const auto rightPoint1 = sf::Vector2f(radius1 + centroid1.x, centroid1.y);

/* Create left half-circle */

    const auto centroid2 = sf::Vector2f(aParameters[1] * mUnit, 0.0f);
    const auto radius2 = aParameters[2] * mUnit;

    const auto fromAngle2 = 1.0f/2.0f*PI;
    const auto toAngle2   = 3.0f/2.0f*PI;

    addArc(lines, centroid2, radius2, fromAngle2, toAngle2, color, aTransform);

    const auto firstPoint2 = sf::Vector2f(radius2 * cosf(fromAngle2) + centroid2.x, radius2 * sinf(fromAngle2) + centroid2.y);
    const auto lastPoint2  = sf::Vector2f(radius2 * cosf(toAngle2) + centroid2.x, radius2 * sinf(toAngle2) + centroid2.y);

/* Bind edges of central and left half-circles */

    addLine(lines, aTransform * firstPoint1, aTransform * lastPoint2, color);
    addLine(lines, aTransform * firstPoint2, aTransform * lastPoint1, color);

/* Create first up-right circle */

    const auto centroid3 = sf::Vector2f(aParameters[3] * mUnit, -aParameters[3] * mUnit);
    const auto radius3 = 1.5f * mUnit;

    addArc(lines, centroid3, radius3, 0.0f, 2.0f * PI, color, aTransform);

    const auto leftUpPoint3    = sf::Vector2f(radius3 * cosf(-3.0f / 4.0f * PI) + centroid3.x, radius3 * sinf(-3.0f / 4.0f * PI) + centroid3.y);
    const auto rightDownPoint3 = sf::Vector2f(radius3 * cosf(1.0f / 4.0f * PI) + centroid3.x, radius3 * sinf(1.0f / 4.0f * PI) + centroid3.y);

/* Bind edges of central half-circle and first up-right circle */

    addLine(lines, aTransform * leftUpPoint3,    aTransform * upPoint1,    color);
    addLine(lines, aTransform * rightDownPoint3, aTransform * rightPoint1, color);

/* Create first down-right circle */

    const auto centroid4 = sf::Vector2f(aParameters[3] * mUnit, aParameters[3] * mUnit);
    const auto radius4 = 1.5f * mUnit;

    addArc(lines, centroid4, radius4, 0.0f, 2.0f * PI, color, aTransform);

    const auto rightUpPoint4  = sf::Vector2f(radius4 * cosf(-1.0f / 4.0f * PI) + centroid4.x, radius4 * sinf(-1.0f / 4.0f * PI) + centroid4.y);
    const auto leftDownPoint4 = sf::Vector2f(radius4 * cosf(3.0f / 4.0f * PI) + centroid4.x, radius4 * sinf(3.0f / 4.0f * PI) + centroid4.y);

/* Bind edges of central half-circle and first down-right circle */

    addLine(lines, aTransform * leftDownPoint4, aTransform * downPoint1,  color);
    addLine(lines, aTransform * rightUpPoint4,  aTransform * rightPoint1, color);

/* Create second up-right circle */

    const auto centroid5 = sf::Vector2f((aParameters[3] + aParameters[4]) * mUnit, -(aParameters[3] + aParameters[4]) * mUnit);
    const auto radius5 = 2.0f * mUnit;

    addArc(lines, centroid5, radius5, 0.0f, 2.0f * PI, color, aTransform);

    const auto leftUpPoint5    = sf::Vector2f(radius5 * cosf(-3.0f / 4.0f * PI) + centroid5.x, radius5 * sinf(-3.0f / 4.0f * PI) + centroid5.y);
    const auto rightDownPoint5 = sf::Vector2f(radius5 * cosf(1.0f / 4.0f * PI) + centroid5.x, radius5 * sinf(1.0f / 4.0f * PI) + centroid5.y);

/* Bind edges of first up-right circle and second up-right circle */

    addLine(lines, aTransform * leftUpPoint5,    aTransform * leftUpPoint3,    color);
    addLine(lines, aTransform * rightDownPoint5, aTransform * rightDownPoint3, color);

/* Create second down-right circle */

    const auto centroid6 = sf::Vector2f((aParameters[3] + aParameters[4]) * mUnit, (aParameters[3] + aParameters[4]) * mUnit);
    const auto radius6 = 2.0f * mUnit;

    addArc(lines, centroid6, radius6, 0.0f, 2.0f * PI, color, aTransform);

    const auto rightUpPoint6  = sf::Vector2f(radius6 * cosf(-1.0f / 4.0f * PI) + centroid6.x, radius6 * sinf(-1.0f / 4.0f * PI) + centroid6.y);
    const auto leftDownPoint6 = sf::Vector2f(radius6 * cosf(3.0f / 4.0f * PI) + centroid6.x, radius6 * sinf(3.0f / 4.0f * PI) + centroid6.y);

/* Bind edges of first down-right circle and second down-right circle */

    addLine(lines, aTransform * leftDownPoint6, aTransform * leftDownPoint4, color);
    addLine(lines, aTransform * rightUpPoint6,  aTransform * rightUpPoint4,  color);

    mRenderWindow.draw(lines);
}

void CoordinateSystem::addArc(sf::VertexArray& aVertexArray, const sf::Vector2f& aCenter, float aR, float aFromAngle, float aToAngle, const sf::Color& aColor, const sf::Transform& aTransform) const
{
    const auto phi = (aToAngle - aFromAngle) / (mPointsNum - 1);

    for (int i = 0; i < mPointsNum - 1; ++i)
    {
        const auto curPhi = i * phi + aFromAngle;
        const auto from = sf::Vector2f(aR * cosf(curPhi + 0.0f) + aCenter.x, aR * sinf(curPhi + 0.0f) + aCenter.y);
        const auto to   = sf::Vector2f(aR * cosf(curPhi + phi ) + aCenter.x, aR * sinf(curPhi + phi ) + aCenter.y);
        addLine(aVertexArray, aTransform * from, aTransform * to, aColor);
    }
}

void CoordinateSystem::addLine(sf::VertexArray &aVertexArray, const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor) const
{
    const auto radianRx = (mAngleR.x + 90.0f) * PI / 180.0f;
    const auto radianRy = (mAngleR.y - 90.0f) * PI / 180.0f;

    const auto r0 = sf::Vector2f(0.0f, 0.0f);
    const auto rx = sf::Vector2f(cosf(radianRx), sinf(radianRx));
    const auto ry = sf::Vector2f(cosf(radianRy), sinf(radianRy));

    aVertexArray.append(sf::Vertex(r0 + rx * aFrom.x + ry * aFrom.y, aColor));
    aVertexArray.append(sf::Vertex(r0 + rx * aTo.x   + ry * aTo.y,   aColor));

//    const auto r0 = sf::Vector2f(0, 0);
//    const auto rx = sf::Vector2f(400, 50);
//    const auto ry = sf::Vector2f(-30, -300);
//
//    auto res = (r0*mW.z + rx*mW.x*aFrom.x + ry*mW.y*aFrom.y) / (mW.z + mW.x*aFrom.x + mW.y*aFrom.y);
//    aVertexArray.append(sf::Vertex(res, aColor));
//
//    res = (r0*mW.z + rx*mW.x*aTo.x + ry*mW.y*aTo.y) / (mW.z + mW.x*aTo.x + mW.y*aTo.y);
//    aVertexArray.append(sf::Vertex(res, aColor));
}
