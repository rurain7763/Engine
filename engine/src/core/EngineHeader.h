#ifndef ENGINEHEADER_H
#define ENGINEHEADER_H

#include "pch.h"

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

enum MOUSE_BUTTON {
	MOUSE_BUTTON_LEFT = 0,
	MOUSE_BUTTON_RIGHT = 1,
	MOUSE_BUTTON_MIDDLE = 2
};

#endif