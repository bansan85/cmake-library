#pragma once

#if defined _WIN32 || defined __CYGWIN__
  #ifdef library2_EXPORTS
    #ifdef __GNUC__
      #define libtest2_PUBLIC __attribute__((dllexport))
    #else
      #define libtest2_PUBLIC __declspec(dllexport)
    #endif
  #elif defined(library2_STATIC)
    #define libtest2_PUBLIC
  #else
    #ifdef __GNUC__
      #define libtest2_PUBLIC __attribute__((dllimport))
    #else
      #define libtest2_PUBLIC __declspec(dllimport)
    #endif
  #endif
  #define libtest2_LOCAL
#else
  #if defined(library2_STATIC)
    #define libtest2_PUBLIC
    #define libtest2_LOCAL
  #else
    #define libtest2_PUBLIC __attribute__((visibility("default")))
    #define libtest2_LOCAL __attribute__((visibility("hidden")))
  #endif
#endif
