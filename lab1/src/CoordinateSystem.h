#ifndef LAB1_COORDINATE_SYSTEM
#define LAB1_COORDINATE_SYSTEM

#include <SFML/Graphics.hpp>

class CoordinateSystem
{
public:
    CoordinateSystem(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit, float& aPointsNum, sf::Vector2f& aAngleR, sf::Vector3f& aW);
    void drawGrid(const sf::Color& aAxisColor = sf::Color(0, 0, 0, 255), const sf::Color& aGridColor = sf::Color(180, 180, 180, 255), const sf::Transform& aTransform = sf::Transform::Identity);
    void drawFigure(const float* aParameters, const sf::Transform& aTransform = sf::Transform::Identity);

    static const float PI;

private:
    void addArc(sf::VertexArray& aVertexArray, const sf::Vector2f& aCenter, float aR, float aFromAngle, float aToAngle, const sf::Color& aColor, const sf::Transform& aTransform) const;
    void addLine(sf::VertexArray &aVertexArray, const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor) const;

    sf::RenderWindow& mRenderWindow;

    sf::Vector2f mSize;

    float& mUnit;
    float& mPointsNum;

    sf::Vector2f& mAngleR;
    sf::Vector3f& mW;
};


#endif //LAB1_COORDINATE_SYSTEM
