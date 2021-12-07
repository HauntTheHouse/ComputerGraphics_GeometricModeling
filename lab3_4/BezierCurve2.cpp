#include "BezierCurve2.h"

BezierCurve2::BezierCurve2(sf::RenderWindow &aRenderWindow, const sf::Vector2i &aSize, float &aUnit)
    : CoordinateSystem(aRenderWindow, aSize, aUnit)
{
}

void BezierCurve2::drawBezierCurve2(const std::vector<sf::Vector2f>& aPoints, int aNumLinesPerCurve, bool aDrawContour, const sf::Transform &aTransform)
{
    sf::VertexArray lines(sf::PrimitiveType::Lines);

    float deltaT = 1.0f/static_cast<float>(aNumLinesPerCurve);

    if (aDrawContour)
    {
        const auto grey = sf::Color::Blue;
        for (int i = 0; i < aPoints.size(); i += 3)
        {
            addLine(lines, aTransform*(aPoints[i+0]*mUnit), aTransform*(aPoints[i+1]*mUnit), grey);
            addLine(lines, aTransform*(aPoints[i+1]*mUnit), aTransform*(aPoints[i+2]*mUnit), grey);
        }
    }

    for (int i = 0; i < aPoints.size(); i += 3)
    {
        float t = 0.0f;
        for (int j = 0; j < aNumLinesPerCurve; ++j)
        {
            const auto p1 = (1.0f - t)*(1.0f - t)*aPoints[i+0]*mUnit + 2.0f*t*(1.0f - t)*aPoints[i+1]*mUnit + t*t*aPoints[i+2]*mUnit;
            t += deltaT;
            const auto p2 = (1.0f - t)*(1.0f - t)*aPoints[i+0]*mUnit + 2.0f*t*(1.0f - t)*aPoints[i+1]*mUnit + t*t*aPoints[i+2]*mUnit;
            addLine(lines, aTransform*p1, aTransform*p2, sf::Color::Red);
        }
    }

    mRenderWindow.draw(lines);
}
