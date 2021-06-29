#include "LK/Assert.h"

LK::ExceptionAssertionFailed::ExceptionAssertionFailed(const char* what, const char* condition, const char* file, int line)
    : Exception(what) {
    sprintf(m_pretty_what, "%s: %s in %s:%d", what, condition, file, line);
}

const char* LK::ExceptionAssertionFailed::what() const noexcept {
    return m_pretty_what;
}

LK::ExceptionAssertionFailed::~ExceptionAssertionFailed() noexcept {
}
