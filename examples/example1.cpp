#include <LK/Buffer.h>
#include <LK/Human.h>

#include <iostream>

int main() {
    LK::Buffer<int> buf(10);
    for (;;) {
        buf.grow_by(buf.size() / 5);
        buf.fill(buf.size());
        std::cout << "now " << buf.size() << " elements, using "
                  << LK::Human::bytes_to_string(buf.used_memory_in_bytes()).data()
                  << std::endl;
        if (buf.used_memory_in_bytes() > 1.5 * LK::Human::GiB) {
            break;
        }
    }
}
