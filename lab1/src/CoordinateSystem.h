#ifndef LAB1_COORDINATE_SYSTEM
#define LAB1_COORDINATE_SYSTEM

#include <SFML/Graphics.hpp>

class CoordinateSystem
{
public:
    CoordinateSystem(sf::RenderWindow& aRenderWindow, const sf::Vector2f& aCenterOfGrid, unsigned int aWidth, unsigned int aHeight);
    void drawGrid(float aUnit);

private:

    sf::RenderWindow& mRenderWindow;

    sf::Vector2f mCenterOfGrid;

    unsigned int mWidth;
    unsigned int mHeight;
};


#endif //LAB1_COORDINATE_SYSTEM
