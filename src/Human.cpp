#include "LK/Human.h"

#include <stdio.h>

LK::Buffer<char> LK::Human::bytes_to_string(size_t n) {
    LK::Buffer<char> buf(20);
    float value = n;
    if (value > PiB) {
        value /= float(PiB);
        sprintf(buf.data(), "%0.2f PiB", value);
    } else if (value > TiB) {
        value /= float(TiB);
        sprintf(buf.data(), "%0.2f TiB", value);
    } else if (value > GiB) {
        value /= float(GiB);
        sprintf(buf.data(), "%0.2f GiB", value);
    } else if (value > MiB) {
        value /= float(MiB);
        sprintf(buf.data(), "%0.2f MiB", value);
    } else if (value > KiB) {
        value /= float(KiB);
        sprintf(buf.data(), "%0.2f KiB", value);
    } else {
        sprintf(buf.data(), "%lu B", n);
    }
    return buf;
}