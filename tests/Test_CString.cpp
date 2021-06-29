#include "LK/Assert.h"
#include "LK/CString.h"
#include "LK/UnitTest.h"
#include <cstring>

int main() {
    {
        LK_TEST_SECTION("empty string");
        LK::CString empty("");
        LK_TEST(empty.length() == 0);
        LK_TEST(empty == "");
        LK_TEST("" == empty);
        LK_TEST(empty == empty);
    }
    {
        LK_TEST_SECTION("regular short string");
        LK::CString words("hello, world");
        LK_TEST(words.length() == strlen(words.data));
        LK_TEST(words == words.data);
        LK_TEST(words.data == words);
        LK_TEST(words == "hello, world");
        LK_TEST(words != "goodbye");
    }
    {
        LK_TEST_SECTION("exceptions");
        LK_TEST_EXPECT_THROW(LK::CString(nullptr), LK::ExceptionAssertionFailed);
        LK_TEST_EXPECT_THROW(auto _ = LK::CString("hi") == nullptr, LK::ExceptionAssertionFailed);
    }
    LK::UnitTest::finalize();
}