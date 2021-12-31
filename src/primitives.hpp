#pragma once

#include <glm/vec3.hpp>

#include "ray.hpp"

namespace rt {

bool intersect_plane(const ray &in, hit_info &hit, const glm::vec3 n, const glm::vec3 p);
bool intersect_sphere(const ray &in, hit_info &hit, const glm::vec3 c, const float radius);

}
