#pragma once

#include <glm/vec3.hpp>

#include "ray.hpp"

namespace rt {

typedef struct {
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;
    float specularity;
    float gloss;
} material;

typedef struct {
    ray out;
    glm::vec3 col;
} surface_interaction;

constexpr material emission_shader(const glm::vec3 col) {
    return {glm::vec3(0), glm::vec3(0), col, 0.f, 0.f};
}

glm::vec3 lambertian_reflect(const glm::vec3 normal);
glm::vec3 glossy_reflect(const glm::vec3 incident, const glm::vec3 normal, const float gloss);

surface_interaction bsdf(const hit_info &hit, const material &material);

}
