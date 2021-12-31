#include "primitives.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "ray.hpp"

namespace rt {

// intersection functions adapted from
//      https://www.iquilezles.org/www/articles/intersectors/intersectors.htm

bool intersect_plane(const ray &in, hit_info &hit, const glm::vec3 n, const glm::vec3 p) {
    float dist = glm::dot(p-in.origin, n) / glm::dot(in.direction, n);
    if (dist < 0.0f) return false;
    hit = {in.at(dist), n, in.direction, dist};
    return true;
}

bool intersect_sphere(const ray &in, hit_info &hit, const glm::vec3 centre, const float radius) {
    auto fc = in.origin - centre;
    float b = glm::dot(fc, in.direction);
    float c = glm::dot(fc, fc) - radius * radius;
    float h = b*b - c;

    if (h < 0.0f) return false;
    h = sqrtf(h);
    float dist = -b-h > 0.0f ? -b-h : -b+h;
    auto pos = in.at(dist);
    auto norm = glm::normalize(pos - centre);
    hit = {pos, norm, in.direction, dist};
    return true;
}

bool intersect_tri(const ray &in, hit_info &hit, glm::vec2 &uv, const glm::vec3 v0, const glm::vec3 v1, const glm::vec3 v2) {
    const auto v1v0 = v1 - v0;
    const auto v2v0 = v2 - v0;
    const auto rov0 = in.origin - v0;

    const auto n = glm::cross(v1v0, v2v0);
    const auto q = glm::cross(rov0, in.direction);

    const float d = 1.f / glm::dot(in.direction, n);
    const float u = d * glm::dot(-q, v2v0);
    const float v = d * glm::dot(q, v1v0);
    const float t = d * glm::dot(-n, rov0);

    if (u<0.f || u>1.f || v<0.f || (u+v)>1.f) return false;
    uv = glm::vec2(u, v);
    hit = {in.at(t), glm::normalize(n), in.direction, t};
    return true;
}

}