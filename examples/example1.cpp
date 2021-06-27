#include <LK/Version.h>

#include <iostream>

int main() {
    auto v = LK::version();
    std::cout << std::boolalpha << (LK::CString(nullptr) == LK::CString("hello")) << std::endl;
}
