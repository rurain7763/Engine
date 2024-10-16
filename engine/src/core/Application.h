#ifndef APPLICATION_H
#define APPLICATION_H

#include "EngineHeader.h"

#include "events/WindowClosedEvent.h"
#include "events/WindowResizedEvent.h"

namespace engine {
    class EG_API Application {
    public:
        Application();
        virtual ~Application();

        void Init();
        void Run();
        void Shutdown();

    private:
        void OnWindowClosed(WindowClosedEvent& event);
        void OnWindowResize(WindowResizedEvent& event);

    private:
        bool _running;

        std::shared_ptr<class DisplayWindow> _window;
    };
};

#endif // APPLICATION_H