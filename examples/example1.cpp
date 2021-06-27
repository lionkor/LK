#include <LK/Buffer.h>
#include <LK/Human.h>

#include <iostream>

int main() {
    LK::Buffer<int> buf(10);
    buf.fill(1);
    LK::Buffer<int> buf2(5);
    for (int i : buf) {
        std::cout << "buf: " << i << std::endl;
    }
    buf2.fill(2);
    for (int i : buf2) {
        std::cout << "buf2: " << i << std::endl;
    }
    buf.append(LK::move(buf2));
    for (int i : buf) {
        std::cout << i << std::endl;
    }
    int k = 0;
    for (int& i : buf) {
        i = k++;
    }
    auto slice = buf.slice(0, 16);
    for (int i : slice) {
        std::cout << "sliced: " << i << std::endl;
    }
}
