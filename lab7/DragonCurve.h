#ifndef DRAGON_CURVE
#define DRAGON_CURVE

#include <CoordinateSystem.h>

class DragonCurve : public CoordinateSystem
{
public:
    DragonCurve(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit);
    void drawDragonCurve(size_t aIterNum);
};


#endif // DRAGON_CURVE
