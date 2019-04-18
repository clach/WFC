#pragma once

#include "../la.h"

class Ray
{
public:
    Ray(const glm::vec3& origin, const glm::vec3& direction);
    Ray(const Ray& ray);

    Ray getTransformedCopy(const glm::mat4& transMat) const;

    glm::vec3 origin;
    glm::vec3 direction;
};
