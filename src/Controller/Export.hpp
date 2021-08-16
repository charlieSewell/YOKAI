#pragma once

#if defined _WIN32 || defined __CYGWIN__
  #ifdef YOKAI_EXPORTS
    #ifdef __GNUC__
      #define YOKAI_API __attribute__ ((dllexport))
    #else
      #define YOKAI_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define YOKAI_API __attribute__ ((dllimport))
    #else
      #define YOKAI_API __declspec(dllimport)
    #endif
  #endif
  #define NOT_EXPORTED
#else
  #if __GNUC__ >= 4
    #define YOKAI_API __attribute__ ((visibility ("default")))
    #define NOT_EXPORTED  __attribute__ ((visibility ("hidden")))
  #else
    #define YOKAI_API
    #define NOT_EXPORTED
  #endif
#endif