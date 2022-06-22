#pragma once

#if defined _WIN32 || defined __CYGWIN__
  #ifdef library4_EXPORTS
    #ifdef __GNUC__
      #define libtest4_PUBLIC __attribute__((dllexport))
    #else
      #define libtest4_PUBLIC __declspec(dllexport)
    #endif
  #elif defined(library4_STATIC)
    #define libtest4_PUBLIC
  #else
    #ifdef __GNUC__
      #define libtest4_PUBLIC __attribute__((dllimport))
    #else
      #define libtest4_PUBLIC __declspec(dllimport)
    #endif
  #endif
  #define libtest4_LOCAL
#else
  #if defined(library4_STATIC)
    #define libtest4_PUBLIC
    #define libtest4_LOCAL
  #else
    #define libtest4_PUBLIC __attribute__((visibility("default")))
    #define libtest4_LOCAL __attribute__((visibility("hidden")))
  #endif
#endif
