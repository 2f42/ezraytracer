#pragma once

#include <glm/vec3.hpp>

#include "ray.hpp"

namespace rt {

typedef struct {
    glm::vec3 diffuse;
    glm::vec3 emission;
} material;

ray bsdf(const hit_info hit, const material material);

}
