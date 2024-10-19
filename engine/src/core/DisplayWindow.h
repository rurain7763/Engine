#ifndef WINDOWS_H
#define WINDOWS_H

#include "EngineHeader.h"

namespace engine {
    class EventBus;
    class EG_API DisplayWindow {
    public:
        DisplayWindow();
        ~DisplayWindow() = default;

        void Init(int width, int height, const char* title);
        void Update();
        void Destroy();

        inline Scope<EventBus>& GetEventBus() { return _eventBus; }
        inline int GetWidth() const { return _width; }
        inline int GetHeight() const { return _height; }

        inline void* GetNativeWindow() const { return _window; }

    private:
        void* _window;
        int _width, _height;

        Scope<EventBus> _eventBus;
    }; 
}

#endif