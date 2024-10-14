#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <stdio.h>

#ifdef PLATFORM_MAC
    #define GL_SILENCE_DEPRECATION
#elif PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#include "GLFW/glfw3.h"

#endif // PCH_H