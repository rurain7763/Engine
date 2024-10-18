#ifndef ENGINEHEADER_H
#define ENGINEHEADER_H

#include "pch.h"

#ifdef PLATFORM_MAC
    #ifdef EG_LINKING_DYNAMIC
        #ifdef BUILD_DLL
            #define EG_API __attribute__((visibility("default")))
        #else
            #define EG_API
        #endif
    #else
	    #define EG_API
    #endif
#elif PLATFORM_WINDOWS
    #ifdef EG_LINKING_DYNAMIC
        #ifdef BUILD_DLL
            #define EG_API __declspec(dllexport)
        #else
            #define EG_API __declspec(dllimport)
        #endif
    #else
        #define EG_API
    #endif
#endif

namespace engine {
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}

#endif