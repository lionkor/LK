#pragma once

#include "Meta.h"
#include "Types.h"
#include <stdio.h>

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
