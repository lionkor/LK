#pragma once

#include "Meta.h"
#include "Types.h"
#include <stdio.h>

/*
 * This is a very *VERY* barebones unit test framework.
 * It does enough for what I need in LK at this time.
 */

namespace LK::UnitTest {
LK_API extern size_t fail_count;
LK_API extern size_t success_count;
[[noreturn]] LK_API void finalize();
}

#define LK_TEST_SECTION(x) printf("-- %s --\n", (x));
#define LK_TEST(x)                         \
    do {                                   \
        if (!(x)) {                        \
            printf("FAILED: %s\n", #x);    \
            LK::UnitTest::fail_count++;    \
        } else {                           \
            printf("OK    : %s\n", #x);    \
            LK::UnitTest::success_count++; \
        }                                  \
    } while (false)

#define LK_TEST_EXPECT_THROW(x, exception_type)                           \
    do {                                                                  \
        bool did_throw = false;                                           \
        try {                                                             \
            x;                                                            \
        } catch (const exception_type&) { did_throw = true; }             \
        if (!did_throw) {                                                 \
            printf("FAILED: %s did not throw %s\n", #x, #exception_type); \
            LK::UnitTest::fail_count++;                                   \
        } else {                                                          \
            printf("OK    : %s did throw %s\n", #x, #exception_type);     \
            LK::UnitTest::success_count++;                                \
        }                                                                 \
    } while (false)
