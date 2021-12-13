#ifndef BEZIER_CURVE2
#define BEZIER_CURVE2

#include <CoordinateSystem.h>

class BezierCurve2 : public CoordinateSystem
{
public:
    BezierCurve2(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit);
    void drawBezierCurve2(const std::vector<sf::Vector2f>& aPoints, int aNumLinesPerCurve, bool aDrawContour, const sf::Transform& aTransform = sf::Transform::Identity);
    static sf::VertexArray getVertexArray(const std::vector<sf::Vector2f>& aPoints, int aNumLinesPerCurve);
private:
};


#endif // BEZIER_CURVE2
