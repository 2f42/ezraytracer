#include <stdio.h>
#include <omp.h>

#include <glm/glm.hpp>

#include "random.h"
#include "scene.hpp"

int main(void) {
    random_seed(12345, 0);

    char *buff = (char *)malloc(512 * 512 * 3);
    int i = 512 * 512;
    char *b = buff;
    do {
        --i;
        glm::vec3 col = rt::sample((i % 512) / 512.f - .5f,
                                   (i / 512) / 512.f - .5f);
        *b++ = (unsigned char) (col.x*255);
        *b++ = (unsigned char) (col.y*255);
        *b++ = (unsigned char) (col.z*255);
    } while (i);

    FILE *fptr = fopen("out.ppm", "wb");
    const char *h = "P6 512 512 255\n";
    fwrite(h, 1, 15, fptr);
    fwrite(buff, 1, 512 * 512 * 3, fptr);
    free(buff);

    fclose(fptr);
    return 0;
}
