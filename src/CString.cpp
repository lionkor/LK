#include "LK/CString.h"
#include "LK/Assert.h"
#include <cstring>

// caching
size_t LK::CString::length() const {
    if (m_length == SIZE_MAX) {
        if (!data) {
            m_length = 0;
        } else {
            m_length = strlen(data);
        }
    }
    return m_length;
}
LK::CString::CString(const char* data)
    : data(data) {
    LK_ASSERT(data);
}

bool LK::CString::operator==(const LK::CString& str) {
    if (!data || !str.data) {
        if (!data && !str.data) {
            return true; // nullptr == nullptr, why not
        }
        LK_ASSERT(data);
        LK_ASSERT(str.data);
        return false; // if asserts are disabled, will always return false.
    }
    return strcmp(data, str.data) == 0;
}

bool LK::CString::operator!=(const LK::CString& str) {
    return !(*this == str);
}

bool operator==(const char* str1, const LK::CString& str2) {
    if (!str1 || !str2.data) {
        if (!str2.data && !str1) {
            return true; // nullptr == nullptr, why not
        }
        LK_ASSERT(str2.data);
        LK_ASSERT(str1);
        return false; // if asserts are disabled, will always return false.
    }
    return strcmp(str2.data, str1) == 0;
}
bool operator!=(const char* str1, const LK::CString& str2) {
    return !(str1 == str2);
}
bool operator==(const LK::CString& str1, const char* str2) {
    return str2 == str1;
}
bool operator!=(const LK::CString& str1, const char* str2) {
    return str2 != str1;
}
