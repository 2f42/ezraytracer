#pragma once

#include <glm/vec3.hpp>

namespace rt {

typedef struct {
    glm::vec3 diffuse;
    glm::vec3 emission;
} material;

}
