#pragma once

#include "Meta.h"
#include "Types.h"

namespace LK {

// A null-terminated string.
// Assumes that the data it holds is not owned by it and is constant.
struct CString final {
    LK_API CString(const char* data);
    LK_API size_t length() const;
    LK_API operator const char*() { return data; }

    LK_API bool operator==(const CString&);
    LK_API bool operator!=(const CString&);

    const char* data { nullptr };

private:
    mutable size_t m_length { SIZE_MAX };
};

} // namespace LK
