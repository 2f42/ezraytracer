// adapted from:
//      https://prng.di.unimi.it/splitmix64.c
//      https://prng.di.unimi.it/xoshiro256starstar.c

#include "random.h"


/*

TODO: make this threadsafe

*/


static uint64_t x;      // splitmix state
static uint64_t s[4];   // xoshiro256** state

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

uint64_t splitmix64(void) {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

void random_seed(uint64_t seed) {
    x = seed;
    s[0] = splitmix64();
    s[1] = splitmix64();
    s[2] = splitmix64();
    s[3] = splitmix64();
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
