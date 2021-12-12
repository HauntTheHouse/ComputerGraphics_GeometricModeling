#ifndef CABINET_PROJECTION
#define CABINET_PROJECTION

#include "CoordinateSystem.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class CabinetProjection : public CoordinateSystem
{
public:
    CabinetProjection(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit);
    void drawCavalierProjection(const std::vector<glm::vec3>& aPoints, float aDegree, const glm::mat4& aTransform);
};


#endif // CABINET_PROJECTION
