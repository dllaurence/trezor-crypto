#ifndef _COMPILERFIX_H
#define _COMPILERFIX_H


#include <stdint.h>

/**********************************************************************
 * LSHIFT
 *
 * Work-around for left shift bug in GCC 3.3.6 that truncates the result
 * of 64-bit shifts.
 *
 * Use a macro so it's polymorphic and we can use it for every
 * occurence of <<, thus avoiding errors identifying 64-bit shifts.
 *
 * N.B. This macro is pretty safe as it evaluates each argument exactly
 * once. Don't change that--in extremis use GCC statement expressions
 * or whatever is required.
 *
 * FIXME: it's not entirely clear that it is safe to always have 1 be
 * unsigned long long, but if it isn't then we get shift overflows.
 *
 **********************************************************************/

#define LSHIFT(x, i) ((x) * (1ULL << (i)))

#define LSHIFT32(x, i) lshift(x, i)


static inline uint64_t lshift(uint64_t x, int i);
static inline uint64_t lshift(uint64_t x, int i)
{

    uint32_t xh = x >> 32;
    uint32_t xl = x;
    return x * (1ULL << i);
}

#endif
