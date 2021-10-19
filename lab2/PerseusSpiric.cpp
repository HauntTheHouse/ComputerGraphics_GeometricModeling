#include "PerseusSpiric.h"
#include <cmath>
#include <iostream>

PerseusSpiric::PerseusSpiric(sf::RenderWindow &aRenderWindow, const sf::Vector2i &aSize, float &aUnit)
    : CoordinateSystem(aRenderWindow, aSize, aUnit)
{
}

void PerseusSpiric::drawPerseusSpiric(float* aParameters, const sf::Transform &aTransform)
{
    sf::VertexArray lines(sf::PrimitiveType::Lines);

    const auto pointsNum = aParameters[0];
    const auto a = aParameters[1];
    auto& curveLength     = aParameters[2];
    auto& curveArea       = aParameters[3];
    auto& curvatureRadius = aParameters[4];

    curveLength = 6.0f * a;
    curveArea = 3.0f / 8.0f * PI * a * a;
    curvatureRadius = 3.0f / 2.0f * a * sinf(PI/2.0f);

    const auto theta = 360.0f / static_cast<float>(pointsNum) * PI / 180.0f;
    auto currentAngle = 0.0f;
    for (int i = 0; i < pointsNum; ++i)
    {
        const auto cos = cosf(currentAngle);
        const auto sin = sinf(currentAngle);
        const auto cosNext = cosf(currentAngle + theta);
        const auto sinNext = sinf(currentAngle + theta);

        const auto pos1 = sf::Vector2f(
            a * cos * cos * cos * mUnit,
            a * sin * sin * sin * mUnit);
        const auto pos2 = sf::Vector2f(
            a * cosNext * cosNext * cosNext* mUnit,
            a * sinNext * sinNext * sinNext* mUnit);

        addLine(lines, aTransform * pos1, aTransform * pos2, sf::Color::Red);
        currentAngle += theta;
    }

    const auto cos = cosf(aParameters[5] * PI/180.0f);
    const auto sin = sinf(aParameters[5] * PI/180.0f);
    const auto tan = sin / cos;

    auto tangentX1 =  50.0f * mUnit, tangentY1 = -tan * tangentX1;
    auto tangentX2 = -50.0f * mUnit, tangentY2 = -tan * tangentX2;

    auto normalX1 =  50.0f * mUnit * tan, normalY1 =  50.0f * mUnit;
    auto normalX2 = -50.0f * mUnit * tan, normalY2 = -50.0f * mUnit;

    sf::Transform trans = aTransform;
    trans.translate(a * cos * cos * cos * mUnit, a * sin * sin * sin * mUnit);

    addLine(lines, trans * sf::Vector2f(tangentX1, tangentY1), trans * sf::Vector2f(tangentX2, tangentY2), sf::Color::Blue);
    addLine(lines, trans * sf::Vector2f(normalX1,  normalY1),  trans * sf::Vector2f(normalX2,  normalY2), sf::Color::Green);

    mRenderWindow.draw(lines);
}