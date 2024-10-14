#ifndef APPLICATION_H
#define APPLICATION_H

#include "EngineHeader.h"
#include "DisplayWindow.h"

#include "events/WindowClosedEvent.h"
#include "events/WindowResizedEvent.h"
#include "events/KeyPressedEvent.h"
#include "events/KeyReleasedEvent.h"
#include "events/MouseButtonPressedEvent.h"
#include "events/MouseButtonReleasedEvent.h"
#include "events/MouseMovedEvent.h"
#include "events/MouseScrolledEvent.h"

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

        void OnKeyPressed(KeyPressedEvent& event);
        void OnKeyReleased(KeyReleasedEvent& event);

        void OnMouseButtonPressed(MouseButtonPressedEvent& event);
        void OnMouseButtonReleased(MouseButtonReleasedEvent& event);
        void OnMouseMoved(MouseMovedEvent& event);
        void OnMouseScrolled(MouseScrolledEvent& event);

    private:
        bool _running;

        std::shared_ptr<DisplayWindow> _window;
    };
};

#endif // APPLICATION_H