#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <typeindex>
#include <functional>
#include <bitset>
#include <fstream>

#include <stdio.h>

#ifdef PLATFORM_MAC
    #define GL_SILENCE_DEPRECATION
#elif PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#endif // PCH_H