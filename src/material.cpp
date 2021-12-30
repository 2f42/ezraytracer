#include "material.hpp"

#include <glm/vec3.hpp>

#include "ray.hpp"
#include "random.h"

namespace rt {

ray bsdf(const hit_info hit, const material material) {
    return {hit.position, lambertian_reflect(hit.normal)};
}

}