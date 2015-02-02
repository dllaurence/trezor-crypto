// compilerfix.c

#include "compilerfix.h"


// Alternative implementation with function + macro--note that a
// pure functional implementation doesn't work.
uint64_t lshift_base(uint64_t x, unsigned i, size_t x_size)
{
    const uint32_t shift31 = 1 << 31; // 31 works fine here

    while (i > 31) {
        x *= shift31;
        i -= 31;
    }

    i = 1 << i;
    x *= i;

    switch (x_size) {
    case 1:
        x &= 0xFF;
        break;
    case 2:
        x &= 0xFFFF;
        break;
    case 4:
        x &= 0xFFFFFFFF;
        break;
    case 8:
        // Do nothing
        break;
    }

    return x;
}


uint64_t rshift_base(uint64_t x, unsigned i)
{
    const uint32_t shift31 = 1 << 31; // 31 works fine here

    while (i > 31) {
        x /= shift31;
        i -= 31;
    }

    i = 1 << i;
    x /= i;

    return x;
}


#if 0
//Another possible implementation

uint64_t rshift_base(uint64_t x, unsigned i, size_t x_size)
{
    return x / lshift_base(1, i, x_size);
}
#endif
