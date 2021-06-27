#pragma once

#include "Buffer.h"
#include "Meta.h"

/*
 * Helpers to make stuff readable and understandable for humans.
 */

namespace LK::Human {
constexpr size_t KiB = 1024;
constexpr size_t MiB = KiB * 1024;
constexpr size_t GiB = MiB * 1024;
constexpr size_t TiB = GiB * 1024;
constexpr size_t PiB = TiB * 1024;
// converts a number of bytes into human readable form, such as "351.2 MiB".
LK_API Buffer<char> bytes_to_string(size_t n);
}