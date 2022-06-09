#pragma once

#if defined _WIN32 || defined __CYGWIN__
  #ifdef library_EXPORTS
    #ifdef __GNUC__
      #define libtest_PUBLIC __attribute__((dllexport))
    #else
      #define libtest_PUBLIC __declspec(dllexport)
    #endif
  #elif defined(library_STATIC)
    #define libtest_PUBLIC
  #else
    #ifdef __GNUC__
      #define libtest_PUBLIC __attribute__((dllimport))
    #else
      #define libtest_PUBLIC __declspec(dllimport)
    #endif
  #endif
  #define libtest_LOCAL
#else
  #if defined(library_STATIC)
    #define libtest_PUBLIC
    #define libtest_LOCAL
  #else
    #define libtest_PUBLIC __attribute__((visibility("default")))
    #define libtest_LOCAL __attribute__((visibility("hidden")))
  #endif
#endif
