// adapted from:
//      https://prng.di.unimi.it/splitmix64.c
//      https://prng.di.unimi.it/xoshiro256starstar.c

#include "random.h"

static __thread uint64_t x;      // splitmix state
static __thread uint64_t s[4];   // xoshiro256** state

static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

uint64_t splitmix64(void) {
    uint64_t z = (x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

uint64_t ranl(void) {
    const uint64_t result = rotl(s[1] * 5, 7) * 9;

    const uint64_t t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;

    s[3] = rotl(s[3], 45);

    return result;
}

double ranf(void) {
    union {
        unsigned long i;
        double f;
    } pun = { ( 0x3FF0000000000000UL | (ranl() >> 12) ) };
    return pun.f - 1.f;
}

void jump(void) {
    static const uint64_t JUMP[] = { 0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c };

    uint64_t s0 = 0;
    uint64_t s1 = 0;
    uint64_t s2 = 0;
    uint64_t s3 = 0;
    for(uint64_t i=0; i < sizeof JUMP / sizeof *JUMP; i++)
        for(int b=0; b < 64; b++) {
            if (JUMP[i] & UINT64_C(1) << b) {
                s0 ^= s[0];
                s1 ^= s[1];
                s2 ^= s[2];
                s3 ^= s[3];
            }
            ranl();	
        }

    s[0] = s0;
    s[1] = s1;
    s[2] = s2;
    s[3] = s3;
}

void random_seed(uint64_t seed, int jumps) {
    x = seed;
    s[0] = splitmix64();
    s[1] = splitmix64();
    s[2] = splitmix64();
    s[3] = splitmix64();

    for (int i=0; i<jumps; i++) {
        jump();
    }
}
