#pragma once

#include <glm/vec3.hpp>

namespace rt {

typedef struct {
    glm::vec3 origin;
    glm::vec3 direction;
} ray;

typedef struct {
    bool hit;
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 incident;
    float distance;
} hit_info;

}
