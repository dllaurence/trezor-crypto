/**
 * Copyright (c) 2013-2014 Tomas Dzetkulic
 * Copyright (c) 2013-2014 Pavol Rusnak
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#include <string.h>
#include <stdlib.h>

#include "testutil.h"


uint8_t *fromhex(const char *str)
{
	static uint8_t buf[128];
	uint8_t c;
	size_t i;
	for (i = 0; i < strlen(str) / 2; i++) {
		c = 0;
		if (str[i*2] >= '0' && str[i*2] <= '9') c += (str[i*2] - '0') << 4;
		if (str[i*2] >= 'a' && str[i*2] <= 'f') c += (10 + str[i*2] - 'a') << 4;
		if (str[i*2] >= 'A' && str[i*2] <= 'F') c += (10 + str[i*2] - 'A') << 4;
		if (str[i*2+1] >= '0' && str[i*2+1] <= '9') c += (str[i*2+1] - '0');
		if (str[i*2+1] >= 'a' && str[i*2+1] <= 'f') c += (10 + str[i*2+1] - 'a');
		if (str[i*2+1] >= 'A' && str[i*2+1] <= 'F') c += (10 + str[i*2+1] - 'A');
		buf[i] = c;
	}
	return buf;
}

char *tohex(const uint8_t *bin, size_t l)
{
	char *buf = (char *)malloc(l * 2 + 1);
	static char digits[] = "0123456789abcdef";
	size_t i;
	for (i = 0; i < l; i++) {
		buf[i*2  ] = digits[(bin[i] >> 4) & 0xF];
		buf[i*2+1] = digits[bin[i] & 0xF];
	}
	buf[l * 2] = 0;
	return buf;
}
