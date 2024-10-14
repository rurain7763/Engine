#ifndef ENGINEHEADER_H
#define ENGINEHEADER_H

#ifdef PLATFORM_MAC
    #ifdef BUILD_DLL
        #define EG_API __attribute__((visibility("default")))
    #else
        #define EG_API
    #endif
#elif PLATFORM_WINDOWS
    #ifdef BUILD_DLL
        #define EG_API __declspec(dllexport)
    #else
        #define EG_API __declspec(dllimport)
    #endif
#endif

#endif