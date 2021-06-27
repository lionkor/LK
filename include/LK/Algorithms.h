#pragma once

#include "Assert.h"
#include <cstring>

namespace LK {

template<class T>
struct RemoveReference { typedef T type; };
template<class T>
struct RemoveReference<T&> { typedef T type; };
template<class T>
struct RemoveReference<T&&> { typedef T type; };

template<class T>
typename RemoveReference<T>::type&& move(T&& a) {
    return static_cast<typename RemoveReference<T>::type&&>(a);
}

template<typename T>
const T& min(const T& x, const T& y) {
    return x < y ? x : y;
}

namespace Memory {
    template<typename T>
    void copy(T* to, const T* from, size_t n) {
        LK_ASSERT(to);
        LK_ASSERT(from);
        for (size_t i = 0; i < n; ++i) {
            to[i] = from[i];
        }
    }
    template<typename T>
    void move(T* to, const T* from, size_t n) {
        LK_ASSERT(to);
        LK_ASSERT(from);
        for (size_t i = 0; i < n; ++i) {
            to[i] = LK::move(from[i]);
        }
    }
    template<typename T>
    void fill(T* buf, size_t n, T&& value) {
        for (size_t i = 0; i < n; ++i) {
            buf[i] = value;
        }
    }
    template<typename T>
    void fill(T* buf, size_t n, const T& value) {
        for (size_t i = 0; i < n; ++i) {
            buf[i] = value;
        }
    }
}
}