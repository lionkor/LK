#include <LK/Buffer.h>
#include <LK/UnitTest.h>

int main() {
    {
        LK_TEST_SECTION("construction, destruction")
        LK::Buffer<int> buf(5);
        LK_TEST(buf.size() == 5);
        LK_TEST_SECTION("fill");
        buf.fill(-3);
        for (size_t i = 0; i < buf.size(); ++i) {
            LK_TEST(buf[i] == -3);
        }
        LK_TEST_SECTION("append");
        buf.append(1);
        LK_TEST(buf[buf.size() - 1] == 1);
        LK_TEST_SECTION("shrink");
        buf.shrink_by(1);
        for (size_t i = 0; i < buf.size(); ++i) {
            auto val = buf[i];
            LK_TEST(buf[i] == -3);
        }
        buf.shrink_by(100);
        LK_TEST(buf.size() == 0);
    }
    LK::UnitTest::finalize();
}
