#pragma once

#if defined _WIN32 || defined __CYGWIN__
  #ifdef library3_EXPORTS
    #ifdef __GNUC__
      #define libtest3_PUBLIC __attribute__((dllexport))
    #else
      #define libtest3_PUBLIC __declspec(dllexport)
    #endif
  #elif defined(library3_STATIC)
    #define libtest3_PUBLIC
  #else
    #ifdef __GNUC__
      #define libtest3_PUBLIC __attribute__((dllimport))
    #else
      #define libtest3_PUBLIC __declspec(dllimport)
    #endif
  #endif
  #define libtest3_LOCAL
#else
  #if defined(library3_STATIC)
    #define libtest3_PUBLIC
    #define libtest3_LOCAL
  #else
    #define libtest3_PUBLIC __attribute__((visibility("default")))
    #define libtest3_LOCAL __attribute__((visibility("hidden")))
  #endif
#endif
