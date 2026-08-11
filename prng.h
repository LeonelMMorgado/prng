/*

 The code written in here is based on the xoroshiro pseudo random number generator available at https://en.wikipedia.org/wiki/Xorshift#xoroshiro
 
 In order to use this single file, use the definition for PRNG_IMPLEMENTATION before including this haeder:
#include ...
#include ...
#define PRNG_IMPLEMENTATION
#include "prng.h"

 */

#ifndef PRNG_H
#define PRNG_H
#include <stdint.h>

typedef struct _prng_state {
	uint64_t s[4];
} Prng_state;

void prng_init(Prng_state *state, uint64_t seed);
uint64_t prng_gen(Prng_state *state);

#endif //PRNG_H

#ifdef PRNG_IMPLEMENTATION

uint64_t _seed_prng(uint64_t *seed) {
	uint64_t result = (*seed += 0x9E3779B97F4A7C15);
	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
	return result ^ (result >> 31);
}

void prng_init(Prng_state *state, uint64_t seed) {
	state->s[0] = _seed_prng(&seed);
	state->s[1] = _seed_prng(&seed);
	state->s[2] = _seed_prng(&seed);
	state->s[3] = _seed_prng(&seed);
}

uint64_t _rol64(uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

uint64_t prng_gen(Prng_state *state) {
	uint64_t *s = state->s;
	uint64_t const result = _rol64(s[1] * 5, 7) * 9;
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];
	
	s[2] ^= t;
	s[3] = _rol64(s[3], 45);

	return result;
}

#endif //PRNG_IMPLEMENTATION
