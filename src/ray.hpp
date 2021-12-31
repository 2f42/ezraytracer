#pragma once

#include <glm/vec3.hpp>

namespace rt {

typedef struct {
    glm::vec3 origin;
    glm::vec3 direction;

    constexpr glm::vec3 at(const float t) const {
        return origin + direction * t;
    }
} ray;

typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 incident;
    float distance;
} hit_info;

}
