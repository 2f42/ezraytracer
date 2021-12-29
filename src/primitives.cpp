#include "primitives.hpp"

#include <algorithm>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "ray.hpp"

namespace rt {

// intersection functions adapted from
//      https://www.iquilezles.org/www/articles/intersectors/intersectors.htm

bool intersect_plane(const ray in, hit_info &hit, const glm::vec3 n, const glm::vec3 p) {
    float dist = glm::dot(p-in.origin, n) / glm::dot(in.direction, n);
    if (dist < 0.0f) return false;
    hit = {in.origin + in.direction * dist, n, in.direction, dist};
    return true;
}

bool intersect_sphere(const ray in, hit_info &hit, const glm::vec3 centre, const float radius) {
    auto fc = in.origin - centre;
    float b = glm::dot(fc, in.direction);
    float c = glm::dot(fc, fc) - radius * radius;
    float h = b*b - c;
    if (h < 0.0f) return false;
    h = sqrtf(h);
    float dist = -b-h > 0.0f ? -b-h : -b+h;
    auto pos = in.origin + in.direction * dist;
    auto norm = glm::normalize(pos - centre);
    hit = {pos, norm, in.direction, dist};
    return true;
}

}