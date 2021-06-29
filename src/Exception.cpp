#include "LK/Exception.h"

LK::Exception::Exception(const char* what)
    : m_what(what) {
}

LK::Exception::~Exception() noexcept {
}

const char* LK::Exception::what() const noexcept { return m_what; }
