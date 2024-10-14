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
    // Add Mac-specific headers here
#elif PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#endif // PCH_H