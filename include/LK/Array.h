#pragma once

#include "Algorithms.h"
#include "Buffer.h"
#include "Types.h"

namespace LK {

template<typename T, size_t Size>
class Array {
public:
    size_t size() const { return Size; }
    T* data() { return m_data; }
    const T* data() const { return m_data; }
    void fill(const T& value) {
        LK::Memory::fill(m_data, Size, value);
    }
    Buffer<T> slice(size_t from, size_t to) {
        LK_ASSERT(from <= to);
        LK_ASSERT(from <= Size);
        LK_ASSERT(to <= Size);
        Buffer<T> buf(to - from);
        LK::Memory::copy(buf.data(), m_data, to - from);
        return buf; // TODO test
    }

private:
    T m_data[Size];
};

}