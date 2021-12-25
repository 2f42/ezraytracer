#ifndef RANDOM_H_
#define RANDOM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    void random_seed (uint64_t seed);
    uint64_t ranl (void);
    double ranf (void);

#ifdef __cplusplus
}
#endif

#endif