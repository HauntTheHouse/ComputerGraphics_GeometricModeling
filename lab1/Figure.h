#ifndef LAB1_COORDINATE_SYSTEM
#define LAB1_COORDINATE_SYSTEM

#include <CoordinateSystem.h>

class Figure : public CoordinateSystem
{
public:
    Figure(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit, float& aPointsNum, sf::Vector2f& aAngleR, bool& aApplyProjective, sf::Vector3f& aW, sf::Vector2f& aR0, sf::Vector2f& aRCoef);
    void drawFigure(const float* aParameters, const sf::Transform& aTransform = sf::Transform::Identity);

private:
    void addArc(sf::VertexArray& aVertexArray, const sf::Vector2f& aCenter, float aR, float aFromAngle, float aToAngle, const sf::Color& aColor, const sf::Transform& aTransform) const;
    void addLine(sf::VertexArray &aVertexArray, const sf::Vector2f& aFrom, const sf::Vector2f& aTo, const sf::Color& aColor) const override;

    float& mPointsNum;

    sf::Vector2f& mAngleR;

    bool& mApplyProjective;

    sf::Vector3f& mW;
    sf::Vector2f& mR0;
    sf::Vector2f &mRCoef;
};


#endif //LAB1_COORDINATE_SYSTEM
