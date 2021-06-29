#pragma once

#ifndef LK_ENABLE_ASSERT
#define LK_ENABLE_ASSERT true
#endif // LK_ENABLE_ASSERT

#include "Exception.h"
#include "Meta.h"
#include <stdio.h>

namespace LK {

class LK_API ExceptionAssertionFailed : public Exception {
public:
    ExceptionAssertionFailed(const char* what, const char* condition, const char* file, int line);
    virtual ~ExceptionAssertionFailed() noexcept;

    const char* what() const noexcept;

private:
    char m_pretty_what[2048];
};

}

#if LK_ENABLE_ASSERT
#include <stdlib.h>
#define LK_ASSERT(x)                                                                        \
    do {                                                                                    \
        if (!(x)) {                                                                         \
            throw LK::ExceptionAssertionFailed("ASSERTION FAILED", #x, __FILE__, __LINE__); \
        }                                                                                   \
    } while (false)
#else
#define LK_ASSERT(x)
#endif // LK_ENABLE_ASSERT
