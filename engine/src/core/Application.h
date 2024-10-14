#ifndef APPLICATION_H
#define APPLICATION_H

#include "EngineHeader.h"
#include "DisplayWindow.h"

class WindowClosedEvent;
class WindowResizedEvent;

class KeyPressedEvent;
class KeyReleasedEvent;

class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class MouseMovedEvent;
class MouseScrolledEvent;

namespace engine {
    class EG_API Application {
    public:
        Application();
        virtual ~Application();
        void Run();

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
        std::unique_ptr<DisplayWindow> _window;
    };
};

#endif // APPLICATION_H