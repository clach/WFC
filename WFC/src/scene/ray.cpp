#include "ray.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin),
    direction(direction)
{}

Ray::Ray(const Ray& ray) : Ray(ray.origin, ray.direction)
{}

Ray Ray::getTransformedCopy(const glm::mat4& transMat) const {
    glm::vec4 newOrigin = glm::vec4(origin, 1);
    glm::vec4 newDir = glm::vec4(direction, 0);

    newOrigin = transMat * newOrigin;
    newDir = transMat * newDir;

    return Ray(glm::vec3(newOrigin), glm::vec3(newDir));
}
