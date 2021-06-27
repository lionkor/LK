#include "LK/UnitTest.h"
#include <cstdlib>

size_t LK::UnitTest::fail_count = 0;
size_t LK::UnitTest::success_count = 0;

void LK::UnitTest::finalize() {
    printf("DONE. Failed %lu/%lu (%0.1f%% succeeded).\n", fail_count, fail_count + success_count, (1 - (fail_count ? double(fail_count) / double(fail_count + success_count) : 0.0)) * 100);
    if (fail_count == 0) {
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}
