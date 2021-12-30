#include "ray.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "random.h"

namespace rt {

glm::vec3 lambertian_reflect(const glm::vec3 normal) {
    const float a = 6.2832f * ranf();
    const float b = 2.f * ranf() - 1.f;
    return glm::normalize(normal + glm::vec3(sqrtf(1.f -b*b) * glm::vec2(cosf(a), sinf(a)), b));
}

glm::vec3 glossy_reflect(const glm::vec3 incident, const glm::vec3 normal, const float gloss) {
    return glm::vec3(0);
}

}