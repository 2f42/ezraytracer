#include <stdio.h>
#include <string.h>
#include <omp.h>

#include <fstream>

#include <glm/glm.hpp>

#include "random.h"
#include "scene.hpp"

#define RES (512)
#define RESF (512.f)

int main(void) {
    char *image = (char *)malloc(RES * RES * 3);
    memset(image, 0, RES*RES*3);
    
    #pragma omp parallel num_threads(4)
    {
        random_seed(123456, omp_get_thread_num());

        #pragma omp for
        for (int y=0; y<RES; y++) {
            for (int x=0; x<RES; x++) {
                int index = (y*RES + x) * 3;
                const float xf = x / RESF - .5f;
                const float yf = y / RESF - .5f;
                auto col = rt::sample(-xf, -yf);
                image[index++] = (unsigned char) (col.r * 255);
                image[index++] = (unsigned char) (col.g * 255);
                image[index++] = (unsigned char) (col.b * 255);
            }
        }
    }

    FILE *fptr = fopen("out.ppm", "wb");
    const char *h = "P6 512 512 255\n";
    fwrite(h, 1, strlen(h), fptr);
    fwrite(image, 1, RES * RES * 3, fptr);
    free(image);
    fclose(fptr);
    return 0;
}
