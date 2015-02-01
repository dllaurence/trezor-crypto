#ifndef _COMPILERFIX_H
#define _COMPILERFIX_H


#include <stdint.h>

/**********************************************************************
 * LSHIFT
 *
 * Work-around for left shift bug in GCC 3.3.6 PPC cross-compiler that
 * truncates the result of 64-bit shifts.
 *
 * It's hard to substitute for left shift--this uses some "interesting"
 * GCC extensions to produce a macro that has the same behavior as the
 * built-in operator (on platforms where the compiler works) in all
 * tested situations where the behavior is defined. This can't be made
 * to work on both 32 and 64 bit quantities in C, though it could in C++.
 *
 * In C the macro is necessary to make it polymorphic so we can use it
 * for every occurence of <<, thus avoiding errors manually identifying
 * 64-bit shifts when used deep in complex expressions where it is
 * difficult to identify the true types by hand including promotion.
 *
 * On our platforms this macro won't produce the same results as a
 * built-in left-shift operator in the undefined cases where the shift
 * is equal to or greater than the number of bits in the left-hand
 * argument. It might be possible to emulate that behavior, but it is
 * platform, compiler, and even compile flags dependent and we really
 * don't want our code to depend on that behavior.
 *
 * N.B. This macro strives to be as safe as a macro can be by evaluating
 * each argument exactly once. Don't change that--in extremis use GCC
 * statement expressions or whatever is required.
 *
 * FIXME: try a
 *
 **********************************************************************/


/* 31 should work, but doesn't. Why? */ \
#define GEM_LSHIFT_MACRO_MAX 30
#define LSHIFT_MACRO(x, i) \
({ \
    const uint32_t gem_LSHIFT_max = 1 << GEM_LSHIFT_MACRO_MAX; \
    \
    /* Evaluate once */ \
    /* These variable names seem to be leaky and apparently need  */ \
    /* to not coincide with any names from the environment at any */ \
    /* usage site. Perhaps ({..}) does not create a new scope?    */ \
    /* tl;dr: dynamic scoping sucks. */ \
    typeof(x) gem_LSHIFT_y = (x); \
    unsigned gem_LSHIFT_j = (i); \
    \
    while (gem_LSHIFT_j > GEM_LSHIFT_MACRO_MAX) { \
        gem_LSHIFT_y *= gem_LSHIFT_max; \
        gem_LSHIFT_j -= GEM_LSHIFT_MACRO_MAX; \
    } \
    gem_LSHIFT_y * (1 << gem_LSHIFT_j); \
})


// Alternative implementation with function + macro--note that a
// pure functional implementation doesn't work.
#define LSHIFT_FUNCTION(x, i) (lshift_base(x, i, sizeof(x)))
static inline uint64_t lshift_base(uint64_t x, unsigned i, size_t x_size);
static inline uint64_t lshift_base(uint64_t x, unsigned i, size_t x_size)
{
    const uint32_t shift31 = 1 << 31; // 31 works fine here

    while (i > 31) {
        x *= shift31;
        i -= 31;
    }

    i = 1 << i;
    uint64_t s = x * i;

    switch (x_size) {
    case 1:
        s &= 0xFF;
        break;
    case 2:
        s &= 0xFFFF;
        break;
    case 4:
        s &= 0xFFFFFFFF;
        break;
    case 8:
        // Do nothing
        break;
    }

#if 0
    if (x_size == 4) {
    }
    else if (x_size != 8) {
        if (x_size
    }
#endif

    return s;
}


#if 0
#define LSHIFT(x, i) (LSHIFT_FUNCTION(x, i))
#else
#define LSHIFT(x, i) (LSHIFT_MACRO(x, i))
#endif


#endif
