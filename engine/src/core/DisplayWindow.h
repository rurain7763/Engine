#ifndef WINDOWS_H
#define WINDOWS_H

#include "EngineHeader.h"
#include "eventbus/EventBus.h"

namespace engine {
    class EG_API DisplayWindow {
    public:
        DisplayWindow();
        virtual ~DisplayWindow() = default;

        void Init(int width, int height, const char* title);
        void Destroy();

        inline std::unique_ptr<EventBus>& GetEventBus() { return _eventBus; }

    private:
        void* _window;
        std::unique_ptr<EventBus> _eventBus;
    }; 
}

#endif