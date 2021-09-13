#ifndef LAB1_COORDINATE_SYSTEM
#define LAB1_COORDINATE_SYSTEM

#include <SFML/Graphics.hpp>

class CoordinateSystem
{
public:
    CoordinateSystem(sf::RenderWindow& aRenderWindow, const sf::Vector2f& aCenterOfGrid, unsigned int aWidth, unsigned int aHeight, float& aUnit, float& aPointsNum);
    void drawGrid();
    void drawFigure(const float* aParameters);

    static const float PI;

private:
    void addArc(sf::VertexArray& aVertexArray, const sf::Vector2f& aCenter, float aR, float aFromAngle, float aToAngle, const sf::Color& aColor) const;
    static void addLine(sf::VertexArray& aVertexArray, const sf::Vertex& aFrom, const sf::Vertex& aTo);

    sf::RenderWindow& mRenderWindow;

    sf::Vector2f mCenterOfGrid;

    unsigned int mWidth;
    unsigned int mHeight;

    float& mUnit;
    float& mPointsNum;
};


#endif //LAB1_COORDINATE_SYSTEM
