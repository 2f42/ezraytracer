#pragma once

#include <glm/vec3.hpp>

namespace rt {

typedef struct {
    glm::vec3 origin;
    glm::vec3 direction;
} ray;

typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 incident;
    float distance;
} hit_info;

glm::vec3 lambertian_reflect(const glm::vec3 normal);
glm::vec3 glossy_reflect(const glm::vec3 incident, const glm::vec3 normal, const float gloss);

}
