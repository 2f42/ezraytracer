#include <stdio.h>
#include <omp.h>

#include <fstream>

#include <glm/glm.hpp>

#include "random.h"
#include "scene.hpp"

int main(void) {
    char *image = (char *)malloc(512 * 512 * 3);
    
    #pragma omp parallel num_threads(8)
    {
        random_seed(123456, omp_get_thread_num());

        #pragma omp for
        for (int y=0; y<512; y++) {
            for (int x=0; x<512; x++) {
                int index = (y*512 + x) * 3;
                const float xf = x / 512.f - .5f;
                const float yf = y / 512.f - .5f;
                auto col = rt::sample(-xf, -yf);
                image[index++] = (unsigned char) (col.r * 255);
                image[index++] = (unsigned char) (col.g * 255);
                image[index++] = (unsigned char) (col.b * 255);
            }
        }
    }

    std::ofstream f;
    f.open("out.ppm", std::ios::out | std::ios::trunc | std::ios::binary);
    f << "P6 512 512 255\n";
    f << image;
    free(image);
    f.close();
    return 0;
}
