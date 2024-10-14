#ifndef WINDOWS_H
#define WINDOWS_H

#include "EngineHeader.h"

namespace engine {
    class EG_API DisplayWindow {
    public:
        DisplayWindow() = default;
        virtual ~DisplayWindow() = default;

        void Init(int width, int height, const char* title);
        void Destroy();

    private:
        void* _window;
    }; 
}

#endif