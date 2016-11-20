#include "cljvm_precompiled.h"

/* For those who don't know what this means, this is the Hamming Weight of the
 * value in binary. Alternatively, image the 1's of a value written in binary
 * are people standing up, and we want to get the population count or popcnt.*/
static uint32_t bit_count(uint32_t value) {
  return __popcnt(value);
}

static uint32_t mask(uint32_t hash, uint32_t shift) {
  return (hash >> shift) & 0b11111;
}

static uint32_t index(uint32_t bitmap, uint32_t bitpos) {
  return bit_count(bitmap & (bitpos - 1));
}
