#include "scene.hpp"

#include <algorithm>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "ray.hpp"
#include "material.hpp"
#include "primitives.hpp"

namespace rt {

material sky(const ray in) {
    const auto SUN_DIR = glm::vec3(.67f, .33f, -.67f);
    const auto SUN_COL = glm::vec3(1.f, 1.f, 1.f);
    const auto SKY_COL = glm::vec3(.529f, .808f, .922f);

    float t = glm::dot(in.direction, SUN_DIR);
    t = glm::smoothstep(0.9f, 0.91f, t);

    return {glm::vec3(0), glm::mix(SKY_COL, SUN_COL, t)};
}

bool shadow_ray(const glm::vec3 pos) {
    const auto SUN_DIR = glm::vec3(.67f, .33f, -.67f);
    hit_info hit;
    material mat;
    return !intersect_scene({pos, SUN_DIR}, hit, mat);
}

bool intersect_scene(const ray in, hit_info &hit, material &mat) {
    hit = {glm::vec3(0), glm::vec3(0), glm::vec3(0), 1000000.f};
    hit_info t_hit;
    bool intersects_scene = false;

    if (intersect_plane(in, t_hit, glm::vec3(0, 1, 0), glm::vec3(0, -.5, 0))) {
        if (t_hit.distance > 0.001f && t_hit.distance < hit.distance) {
            hit = t_hit;
            mat = {glm::vec3(.5f), glm::vec3(0)};
            intersects_scene = true;
        }
    }

    if (intersect_sphere(in, t_hit, glm::vec3(0,-.3,8.), .2)) {
        if (t_hit.distance > 0.001f && t_hit.distance < hit.distance) {
            hit = t_hit;
            mat = {glm::vec3(.75f), glm::vec3(0)};
            intersects_scene = true;
        }
    }

    if (!intersects_scene) {
        mat = sky(in);
    }

    return intersects_scene;
}

glm::vec3 sample(const ray in, const int depth) {
    if (depth <= -1) return glm::vec3(0);

    hit_info hit;
    material mat;

    bool intersects_scene = intersect_scene(in, hit, mat);
    if (!intersects_scene) return mat.emission;
    
    float dcol = 0.f;
    if (shadow_ray(hit.position)) {
        dcol = std::clamp(
            glm::dot(hit.normal, glm::vec3(.67f, .33f, -.67f)),
            0.f, 1.f
        );
    }
    
    ray r = {hit.position, glm::normalize(glm::reflect(hit.incident, hit.normal))};

    return mat.diffuse * (dcol + sample(r, depth-1)) + mat.emission;
}

glm::vec3 get_pixel(const float x, const float y) {
    const auto CAMERA = glm::vec3(0, 0, -5.f);
    ray r = {CAMERA, glm::normalize(glm::vec3(x, y, 0) - CAMERA)};

    return glm::clamp(sample(r, 8), glm::vec3(0), glm::vec3(1));
}

}
