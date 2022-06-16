#pragma once

// Platform checking
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define _PLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "Only 64-bit windows is supported!"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    #define _PLATFORM_LINUX 1
#elif defined(__unix__)
    #define _PLATFORM_UNIX 1
#elif defined(__APPLE__)
    #define _PLATFORM_APPLE 1
#else
    #error "Unable to check system!"
#endif



// Compiler checking
#if defined(_MSC_VER)
    #define _COMPILER_MSVC 1
#elif defined(__GNUC__)
    #define _COMPILER_GCC 1
#elif defined(__clang__)
    #define _COMPILER_CLANG 1
#elif defined(__MINGW32__)
    #define _COMPILER_MINGW32 1
#elif defined(__MINGW64__)
    #define _COMPILER_MINGW64 1
#endif



// Declaring ENGINE_API macro
#ifdef _LINKING_SHARED
    #if _BUILD_LIBRARY
        #ifdef _COMPILER_MSVC
            #define ENGINE_API __declspec(dllexport)
        #else
            #define ENGINE_API __attribute((visibility("default")))
        #endif
    #else
        #ifdef _COMPILER_MSVC
            #define ENGINE_API __declspec(dllimport)
        #else
            #define ENGINE_API
        #endif
    #endif
#else
    #define ENGINE_API
#endif



// Static assertion
#if defined(__COMPILER_CLANG) || defined(__COMPILER_GCC)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

#ifdef FORCEINLINE
    #undef FORCEINLINE
#endif

#ifdef _COMPILER_MSVC
    #define FORCEINLINE __forceinline
#elif defined(_COMPILER_GCC)
    #define FORCEINLINE __attribute__((always_inline))
#else
    #define FORCEINLINE inline
#endif

#ifdef _PLATFORM_WINDOWS
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#ifdef _PLATFORM_UNIX
    #define _PLATFORM_TEXT_IS_CHAR16 1
#endif
