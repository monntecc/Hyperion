#pragma once

// Platform detection
#ifdef _WIN32
	/* Windows x64/x86 */
    #ifdef _WIN64
	    /* Windows x64  */
        #define HR_PLATFORM_WINDOWS
    #else
	    /* Windows x86 */
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    /* TARGET_OS_MAC exists on all the platforms
    * so we must check all of them (in this order)
    * to ensure that we're running on MAC
    * and not some other Apple platform */
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define HR_PLATFORM_IOS
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #define HR_PLATFORM_MACOS
        #error "MacOS is not supported!"
    #else
        #error "Unknown Apple platform!"
    #endif
/* We also have to check __ANDROID__ before __linux__
* since android is based on the linux kernel
* it has __linux__ defined */
#elif defined(__ANDROID__)
    #define HR_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__linux__)
    #define HR_PLATFORM_LINUX
#else
	/* Unknown compiler/platform */
    #error "Unknown platform!"
#endif // End of platform detection

// DLL support
#ifdef HR_PLATFORM_WINDOWS
    #if HR_DYNAMIC_LINK
        #ifdef HR_BUILD_DLL
            #define HYPERION_API __declspec(dllexport)
        #else
            #define HYPERION_API __declspec(dllimport)
        #endif // End of DLL support
    #else
        #define HYPERION_API
    #endif
#endif

#ifdef HR_PLATFORM_LINUX
    #if HR_DYNAMIC_LINK
        #ifdef HR_BUILD_DLL
            #define HYPERION_API __attribute__((visibility("default")))
        #else
            #define HYPERION_API
        #endif // End of DLL support
    #else
        #define HYPERION_API
    #endif
#endif

#ifndef HR_PLATFORM_WINDOWS
    #ifndef HR_PLATFORM_LINUX
        #error Hyperion only supports Windows and Linux!
    #endif
#endif