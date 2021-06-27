#pragma once

#ifndef LK_ENABLE_ASSERT
#define LK_ENABLE_ASSERT true
#endif // LK_ENABLE_ASSERT

#if LK_ENABLE_ASSERT
#include <cassert>
#define LK_ASSERT(x) assert(x)
#else
#define LK_ASSERT(x)
#endif // LK_ENABLE_ASSERT
