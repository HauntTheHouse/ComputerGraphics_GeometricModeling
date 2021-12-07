#ifndef PERSEUS_SPIRIC
#define PERSEUS_SPIRIC

#include <CoordinateSystem.h>

class PerseusSpiric : public CoordinateSystem
{
public:
    PerseusSpiric(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit);
    void drawPerseusSpiric(float* aParameters, const sf::Transform& aTransform = sf::Transform::Identity);
};


#endif //PERSEUS_SPIRIC
