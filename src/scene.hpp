#pragma once

#include <glm/vec3.hpp>

#include "ray.hpp"
#include "material.hpp"

namespace rt {

material sky(const ray in);
bool shadow_ray(const glm::vec3 pos);
bool intersect_scene(const ray in, hit_info &hit, material &mat);
glm::vec3 sample(const ray in);
glm::vec3 get_pixel(const float x, const float y);

}
