#include <glm/glm.hpp>
#include <stdio.h>
#include "random.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        random_seed(12367);
    } else {
        random_seed(atol(argv[1]));
    }

    printf("%F, %F, %F\n", ranf(), ranf(), ranf());

    return 0;
}