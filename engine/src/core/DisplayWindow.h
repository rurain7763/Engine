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
        void PollEvents();
        void Destroy();

        inline Scope<EventBus>& GetEventBus() { return _data.eventBus; }
        inline int GetWidth() const { return _data.width; }
        inline int GetHeight() const { return _data.height; }

        inline void* GetNativeWindow() const { return _data.window; }

    private:
        struct Data {
            void* window;
            int width, height;
            Scope<EventBus> eventBus;
        };

        Data _data;
    }; 
}

#endif