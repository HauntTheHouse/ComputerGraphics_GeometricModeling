#include "Torus.h"

void Torus::findMaxMin()
{
    mMax = {-1000.0f, -1000.0f};
    mMin = {1000.0f, 1000.0f};
    for (size_t i = 0; i < mTexture.getVertexCount(); ++i)
    {
        if (mTexture[i].position.x > mMax.x)
        {
            mMax.x = mTexture[i].position.x;
        }
        if (mTexture[i].position.y > mMax.y)
        {
            mMax.y = mTexture[i].position.y;
        }
        if (mTexture[i].position.x < mMin.x)
        {
            mMin.x = mTexture[i].position.x;
        }
        if (mTexture[i].position.y < mMin.y)
        {
            mMin.y = mTexture[i].position.y;
        }
    }
}

Torus::Torus(sf::RenderWindow &aRenderWindow, const sf::Vector2i &aSize, float &aUnit, const sf::VertexArray& aTexture)
    : CoordinateSystem(aRenderWindow, aSize, aUnit)
    , mTexture(aTexture)
{
    findMaxMin();
    for (size_t i = 0; i < mTexture.getVertexCount(); ++i)
    {
        mTexture[i].position = {(mTexture[i].position.x - mMin.x) / (mMax.x - mMin.x) * 0.96f + 0.02f, (mTexture[i].position.y - mMin.y) / (mMax.y - mMin.y) * 0.96f + 0.02f};
    }

}

void Torus::drawTorus(float aMainRadius, float aTubeRadius, int aNumMainSegment, int aNumTubeSegment, float aDegree, const glm::mat4& aTransform)
{
    sf::VertexArray lines(sf::PrimitiveType::Lines);

    const auto radian = glm::radians(aDegree);

    glm::mat4 proj(
            1.0f,                        0.0f,                       0.0f, 0.0f,
            0.0f,                        1.0f,                       0.0f, 0.0f,
            -1.0f/2.0f*glm::cos(radian), -1.0f/2.0f*glm::sin(radian), 0.0f, 0.0f,
            0.0f,                        0.0f,                       0.0f, 1.0f
    );

    auto mainSegmentAngleStep = glm::radians(360.0f / float(aNumMainSegment));
    auto tubeSegmentAngleStep = glm::radians(360.0f / float(aNumTubeSegment));
    auto mainSegmentTextureStep = 1.0f / float(aNumMainSegment);
    auto tubeSegmentTextureStep = 1.0f / float(aNumTubeSegment);

    auto curMainSegmentAngle = 0.0f;
    auto curMainSegmentTexCoordV = 0.0f;

    for (auto i = 0; i <= aNumMainSegment; i++)
    {
        auto sinMainSegment = glm::sin(curMainSegmentAngle);
        auto cosMainSegment = glm::cos(curMainSegmentAngle);

        auto sinMainSegmentNext = glm::sin(curMainSegmentAngle + mainSegmentAngleStep);
        auto cosMainSegmentNext = glm::cos(curMainSegmentAngle + mainSegmentAngleStep);

        auto curTubeSegmentAngle = 0.0f;
        auto curTubeSegmentTexCoordU = 0.0f;

        for (auto j = 0; j <= aNumTubeSegment; j++)
        {
            auto sinTubeSegment = glm::sin(curTubeSegmentAngle);
            auto cosTubeSegment = glm::cos(curTubeSegmentAngle);

            auto sinTubeSegmentNext = glm::sin(curTubeSegmentAngle + tubeSegmentAngleStep);
            auto cosTubeSegmentNext = glm::cos(curTubeSegmentAngle + tubeSegmentAngleStep);

            auto point = glm::vec3(
                    (aMainRadius + aTubeRadius * cosTubeSegment)*cosMainSegment,
                    aTubeRadius*sinTubeSegment,
                    (aMainRadius + aTubeRadius * cosTubeSegment)*sinMainSegment)* mUnit;

            auto point1 = proj * aTransform * glm::vec4(glm::vec3(
                    (aMainRadius + aTubeRadius * cosTubeSegment)*cosMainSegment,
                    aTubeRadius*sinTubeSegment,
                    (aMainRadius + aTubeRadius * cosTubeSegment)*sinMainSegment
            ) * mUnit, 1.0f);
            auto point2 = proj * aTransform * glm::vec4(glm::vec3(
                    (aMainRadius + aTubeRadius * cosTubeSegmentNext)*cosMainSegment,
                    aTubeRadius*sinTubeSegmentNext,
                    (aMainRadius + aTubeRadius * cosTubeSegmentNext)*sinMainSegment
            ) * mUnit, 1.0f);
            auto point3 = proj * aTransform * glm::vec4(glm::vec3(
                    (aMainRadius + aTubeRadius * cosTubeSegmentNext)*cosMainSegmentNext,
                    aTubeRadius*sinTubeSegmentNext,
                    (aMainRadius + aTubeRadius * cosTubeSegmentNext)*sinMainSegmentNext
            ) * mUnit, 1.0f);
            auto point4 = proj * aTransform * glm::vec4(glm::vec3(
                    (aMainRadius + aTubeRadius * cosTubeSegment)*cosMainSegmentNext,
                    aTubeRadius*sinTubeSegment,
                    (aMainRadius + aTubeRadius * cosTubeSegment)*sinMainSegmentNext
            ) * mUnit, 1.0f);

            addLine(lines, {point1.x, point1.y}, {point2.x, point2.y}, sf::Color::Red);
            addLine(lines, {point2.x, point2.y}, {point3.x, point3.y}, sf::Color::Red);
            addLine(lines, {point3.x, point3.y}, {point4.x, point4.y}, sf::Color::Red);
            addLine(lines, {point4.x, point4.y}, {point1.x, point1.y}, sf::Color::Red);

            auto textureCoordinate = glm::vec2(curTubeSegmentTexCoordU, curMainSegmentTexCoordV);
            mTextureCoordinates[textureCoordinate.x][textureCoordinate.y] = point;

            curTubeSegmentAngle += tubeSegmentAngleStep;
            curTubeSegmentTexCoordU += tubeSegmentTextureStep;
        }

        curMainSegmentAngle += mainSegmentAngleStep;
        curMainSegmentTexCoordV += mainSegmentTextureStep;
    }

    sf::VertexArray texture(sf::PrimitiveType::Lines);

    for (size_t i = 0; i < mTexture.getVertexCount() - 1; ++i)
    {
        auto lowerBound = (mTextureCoordinates.lower_bound(mTexture[i].position.x))->second.lower_bound(mTexture[i].position.y);
        auto lowerTrans = proj * aTransform * glm::vec4(lowerBound->second, 1.0f);
        texture.append(sf::Vertex({lowerTrans.x, lowerTrans.y}, sf::Color::Blue));
    }

    sf::VertexArray zAxis(sf::PrimitiveType::Lines);

    glm::vec4 startZ = proj * glm::vec4(0.0f, 0.0f, -100.0f * mUnit, 1.0f);
    glm::vec4 endZ =   proj * glm::vec4(0.0f, 0.0f,  100.0f * mUnit, 1.0f);

    addLine(zAxis, {startZ.x, startZ.y}, {endZ.x, endZ.y}, sf::Color::Black);
    mRenderWindow.draw(zAxis);
    mRenderWindow.draw(lines);
    mRenderWindow.draw(texture);
    mRenderWindow.draw(mTexture);
    mTextureCoordinates.clear();
}
