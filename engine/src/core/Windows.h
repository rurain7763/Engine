#ifndef WINDOWS_H
#define WINDOWS_H

#include "EngineHeader.h"

namespace engine {
    class EG_API Windows {
    public:
        Windows() = default;
        virtual ~Windows() = default;

        void Init(int width, int height, const char* title);
        void Destroy();

    private:
        struct GLFWwindow* _window;
    };
}

#endif