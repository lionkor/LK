#include <LK/Array.h>
#include <LK/UnitTest.h>

int main() {
    LK_TEST_SECTION("array initialization");
    LK::Array<int, 12> arr;
    LK_TEST(arr.size() == 12);
    LK_TEST(arr.data() != nullptr);
    LK::UnitTest::finalize();
}