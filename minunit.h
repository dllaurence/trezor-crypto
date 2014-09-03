/* file: minunit.h
 *
 * A minimal unit test framework that can run in any environment that supports
 * C itself without even the standard library.
 *
 * Based on http://www.jera.com/techinfo/jtns/jtn002.html
 *
 * */


#define mu_assert(message, test) do { if (!(test)) return message; } while (0)

#define mu_run_test(test) do { const char *message = test(); tests_run++; \
                               if (message) return message; } while (0)

extern int tests_run;

// Alias test function pointer for convenience
typedef const char *(*minunit_test_function)(void);

// Macros to aid conversion of Check tests
#define ck_assert_int_eq(LHS, RHS) mu_assert(#LHS " == " #RHS, (LHS) == (RHS))
#define ck_assert_str_eq(LHS, RHS) mu_assert("(string equality)", strcmp((LHS),(RHS)) == 0)
#define ck_assert_msg(TEST, ...) mu_assert("Missing Msg", (TEST))
