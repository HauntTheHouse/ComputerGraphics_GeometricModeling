#ifndef TORUS
#define TORUS

#include "CoordinateSystem.h"
#include <glm/glm.hpp>
#include <map>

class Torus : public CoordinateSystem
{
public:
    Torus(sf::RenderWindow& aRenderWindow, const sf::Vector2i& aSize, float& aUnit, const sf::VertexArray& aTexture);
    void drawTorus(float v1, float v2, int aNumMainSegment, int aNumTubeSegment, float aDegree, const glm::mat4& aTransform);
private:
    void findMaxMin();

    sf::VertexArray mTexture;
    std::map<float, std::map<float, glm::vec3>> mTextureCoordinates;
    glm::vec2 mMax;
    glm::vec2 mMin;
};


#endif // TORUS
