#ifndef _COMPILERFIX_H
#define _COMPILERFIX_H


#include <stdint.h>


// GCC 3.3.6 from Thales' SDK truncates 64-bit values after shifting them!
// This is a workaround for the time being.
inline uint64_t lshift64(uint64_t x, unsigned shift);
inline uint64_t lshift64(uint64_t x, unsigned shift)
{
    uint64_t y = 1 << shift;
    return x * y;
}

#endif
