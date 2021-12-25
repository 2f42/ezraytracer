#include <glm/glm.hpp>

int main(void) {
    glm::vec3 a = glm::vec3(1, 2, 3);
    glm::vec3 b = glm::vec3(1, 1, 1);
    return glm::dot(a, b);
}