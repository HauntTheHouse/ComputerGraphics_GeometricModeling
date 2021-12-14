#include "DragonCurve.h"

const float ONE_SQRT2 = 0.70710678118f;

DragonCurve::DragonCurve(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit)
    : CoordinateSystem(aRenderWindow, aSize, aUnit)
{
}

void DragonCurve::drawDragonCurve(size_t aIterNum)
{
    sf::VertexArray lines(sf::PrimitiveType::LinesStrip);

    addLine(lines, {0.0f, 0.0f}, {mUnit, 0.0f}, sf::Color::Blue);

    for (int i = 0; i < aIterNum; ++i)
    {
        auto linesSize = lines.getVertexCount();

        sf::Transform trans = sf::Transform::Identity;
        auto endPos = lines[linesSize - 1].position;
        trans.translate(endPos);
        trans.rotate(-90.0f);

        for (int j = linesSize - 2; j >= 0 ; --j)
        {
            lines.append(sf::Vertex((trans * (lines[j].position - endPos)), sf::Color::Blue));
        }
    }

    mRenderWindow.draw(lines);
}
