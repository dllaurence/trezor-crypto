#ifndef _COMPILERFIX_H
#define _COMPILERFIX_H


#include <stdint.h>
#include <stddef.h>

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


// FIXME: re-write these to expand to an if (not #if, which doesn't work)
// on the sizeof the argument so only 64-bit shifts get slowed down

// Alternative implementation with function + macro--note that a
// pure functional implementation doesn't work.
#define LSHIFT_FUNCTION(x, i) (lshift_base(x, i, sizeof(x)))
// Would like this to be static inline, but 3.3.6 can't inline it
uint64_t lshift_base(uint64_t x, unsigned i, size_t x_size);

#define RSHIFT_FUNCTION(x, i) (rshift_base(x, i))
// Would like this to be static inline, but 3.3.6 can't inline it
uint64_t rshift_base(uint64_t x, unsigned i);


#if 1
#define LSHIFT(x, i) (LSHIFT_FUNCTION(x, i))
#define RSHIFT(x, i) (RSHIFT_FUNCTION(x, i))
#else
#define LSHIFT(x, i) (LSHIFT_MACRO(x, i))
#endif


#endif
