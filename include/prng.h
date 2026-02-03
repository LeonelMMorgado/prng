#ifndef _PRNG_H
#define _PRNG_H
/*
 
 The code written in here is based on the xoroshiro pseudo random number generator available at https://en.wikipedia.org/wiki/Xorshift#xoroshiro
 
 */
#include <stdint.h>

#define SEED_CONST 0x9E3779B97F4A7C15

typedef struct _prng_state {
	uint64_t state_count[4];
} prng_state;

uint64_t prng_gen(prng_state *state);

void prng_init(prng_state *state, uint64_t seed);

#endif
