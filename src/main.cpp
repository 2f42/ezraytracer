#include <glm/glm.hpp>
#include <stdio.h>
#include <omp.h>
#include "random.h"

int main(int argc, char **argv) {

    #pragma omp parallel num_threads(8)
    {
        if (argc != 2) {
            random_seed(12367, omp_get_thread_num());
        } else {
            random_seed(atol(argv[1]), omp_get_thread_num());
        }
    
        printf("%F, %F, %F\n", ranf(), ranf(), ranf());
    }

    return 0;
}