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

#ifndef __TESTLIB_H__
#define __TESTLIB_H__

#include "minunit.h"


// test vector 1 from https://en.bitcoin.it/wiki/BIP_0032_TestVectors
const char *test_bip32_vector_1(void);

// test vector 2 from https://en.bitcoin.it/wiki/BIP_0032_TestVectors
const char *test_bip32_vector_2(void);

const char *test_bip32_compare(void);

const char *test_rfc6979(void);

const char *test_sign_speed(void);

const char *test_verify_speed(void);

// test vectors from http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors
// Uses OpenSSL, which isn't available.
//const char *test_aes(void);

// test vectors from http://stackoverflow.com/questions/15593184/pbkdf2-hmac-sha-512-test-vectors
const char *test_pbkdf2(void);

const char *test_mnemonic(void);

const char *test_mnemonic_check(void);

const char *test_address(void);

const char *test_pubkey_validity(void);

const char *test_wif(void);

const char *test_address_decode(void);

const char *test_ecdsa_der(void);


// Null-terminated array of test functions for convenience
extern minunit_test_function test_suite[];

// run suite
const char *run_suite(void);

#endif
