#include "CabinetProjection.h"
#include <glm/glm.hpp>

CabinetProjection::CabinetProjection(sf::RenderWindow &aRenderWindow, const sf::Vector2i &aSize, float &aUnit)
    : CoordinateSystem(aRenderWindow, aSize, aUnit)
{
}

void CabinetProjection::drawCavalierProjection(const std::vector<glm::vec3> &aPoints, float aDegree, const glm::mat4& aTransform)
{
    sf::VertexArray lines(sf::PrimitiveType::Lines);
    const auto radian = glm::radians(aDegree);

    glm::mat4 proj(
         1.0f,                        0.0f,                       0.0f, 0.0f,
         0.0f,                        1.0f,                       0.0f, 0.0f,
        -1.0f/2.0f*glm::cos(radian), -1.0f/2.0f*glm::sin(radian), 0.0f, 0.0f,
         0.0f,                        0.0f,                       0.0f, 1.0f
    );

    glm::vec4 startZ = proj * glm::vec4(0.0f, 0.0f, -100.0f * mUnit, 1.0f);
    glm::vec4 endZ =   proj * glm::vec4(0.0f, 0.0f,  100.0f * mUnit, 1.0f);

    addLine(lines, {startZ.x, startZ.y}, {endZ.x, endZ.y}, sf::Color::Blue);

    for (size_t i = 0; i < aPoints.size(); i += 2)
    {
        const auto transPoint1 = proj * aTransform * glm::vec4(aPoints[i+0] * 5.0f * mUnit, 1.0f);
        const auto transPoint2 = proj * aTransform * glm::vec4(aPoints[i+1] * 5.0f * mUnit, 1.0f);
        addLine(lines, {transPoint1.x, transPoint1.y}, {transPoint2.x, transPoint2.y}, sf::Color::Red);
    }

    mRenderWindow.draw(lines);
}
