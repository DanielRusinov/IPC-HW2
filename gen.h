#ifndef GEN_H_
#define GEN_H_

#include <stdlib.h>
#include <stdint.h>

#define GEN_BLOCK_SIZE (4096)

void generate(void* ptr, uint32_t seed);

int64_t verify(void* ptr);

void generateFull(void* ptr, uint32_t seed, uint32_t step);

int64_t verifyFull(void* ptr, uint32_t step);

#endif
