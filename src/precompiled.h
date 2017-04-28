#include <stdint.h>
#include <limits.h>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLJVM_PACK(__declaration__) \
    __pragma(pack(push, 1)) __declaration__ __pragma( pack(pop) )
#endif
