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
 **********************************************************************/

#define LSHIFT(x, i) ((x) * (1 << (i)))


#endif
