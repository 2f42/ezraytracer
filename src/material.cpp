#include "material.hpp"

#include <stdio.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "ray.hpp"
#include "random.h"

namespace rt {

glm::vec3 lambertian_reflect(const glm::vec3 normal) {
    const float a = 6.2832f * ranf();
    const float b = 2.f * ranf() - 1.f;
    return glm::normalize(normal + glm::vec3(sqrtf(1.f -b*b) * glm::vec2(cosf(a), sinf(a)), b));
}

// adapted from https://www.shadertoy.com/view/XdyyDd
glm::vec3 glossy_reflect(const glm::vec3 incident, const glm::vec3 normal, const float gloss) {
    const float a = ranf();
    const float ct = sqrtf(1.f - a*a);
    const float st = sqrtf(1.f - ct*ct);
    const float p = ranf() * 6.2832f;
    auto v = glm::vec3(st * cosf(p), st * sinf(p), ct);
    return glm::normalize(glm::reflect(incident, normal) + v * gloss);
}

surface_interaction bsdf(const hit_info &hit, const material &material) {
    const auto out = glm::reflect(hit.incident, hit.normal);
    return {{hit.position, glossy_reflect(hit.incident, hit.normal, .5f)}, glm::vec3(1)};
}

}