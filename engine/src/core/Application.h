#ifndef APPLICATION_H
#define APPLICATION_H

#include "EngineHeader.h"
#include "DisplayWindow.h"
#include "events/KeyPressedEvent.h"

#include <memory>

namespace engine {
    class EG_API Application {
    public:
        Application();
        virtual ~Application();
        void Run();

    private:
        void OnKeyPressed(KeyPressedEvent& event);

    private:
        std::unique_ptr<DisplayWindow> _window;
    };
};

#endif // APPLICATION_H