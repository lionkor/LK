#pragma once

// clang-format off
#if defined _WIN32 || defined __CYGWIN__
  #ifdef LK_BUILDING_DLL
    #ifdef __GNUC__
      #define LK_API __attribute__ ((dllexport))
    #else
      #define LK_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define LK_API __attribute__ ((dllimport))
    #else
      #define LK_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
#else
  #if __GNUC__ >= 4
    #define LK_API __attribute__ ((visibility ("default")))
  #else
    #define LK_API
  #endif
#endif
// clang-format on
