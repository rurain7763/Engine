#ifdef PLATFORM_MAC
#include "../DisplayWindow.h"
#include "../Logger.h"

#include "../DisplayWindow.h"
#include "../Logger.h"

#include "EventBus.h"
#include "../events/WindowClosedEvent.h"
#include "../events/WindowResizedEvent.h"
#include "../events/KeyPressedEvent.h"
#include "../events/KeyReleasedEvent.h"
#include "../events/MouseButtonPressedEvent.h"
#include "../events/MouseButtonReleasedEvent.h"
#include "../events/MouseMovedEvent.h"
#include "../events/MouseScrolledEvent.h"

#include "GLFW/glfw3.h"

namespace engine {
    DisplayWindow::DisplayWindow() {
        _data.eventBus = std::make_unique<EventBus>();
    }

    void DisplayWindow::Init(int width, int height, const char* title) {
        EG_ASSERT(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        EG_ASSERT(window != nullptr, "Failed to create window");

        glfwMakeContextCurrent(window);

        _data.window = window;
        _data.width = width;
        _data.height = height;

        glfwSetWindowUserPointer(window, &_data);

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            Data* data = (Data*)glfwGetWindowUserPointer(window);
            data->eventBus->Publish<WindowClosedEvent>();
        });

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            Data* data = (Data*)glfwGetWindowUserPointer(window);
            data->width = width;
            data->height = height;
            data->eventBus->Publish<WindowResizedEvent>(width, height);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            Data* data = (Data*)glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS:
                data->eventBus->Publish<KeyPressedEvent>(key);
                break;
            case GLFW_RELEASE:
                data->eventBus->Publish<KeyReleasedEvent>(key);
                break;
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            Data* data = (Data*)glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS:
                data->eventBus->Publish<MouseButtonPressedEvent>(button);
                break;
            case GLFW_RELEASE:
                data->eventBus->Publish<MouseButtonReleasedEvent>(button);
                break;
            }
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            Data* data = (Data*)glfwGetWindowUserPointer(window);
            data->eventBus->Publish<MouseMovedEvent>(static_cast<int>(xpos), static_cast<int>(ypos));
            });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            Data* data = (Data*)glfwGetWindowUserPointer(window);
            data->eventBus->Publish<MouseScrolledEvent>(xoffset, yoffset);
        });
    }

    void DisplayWindow::Update() {
        glfwSwapBuffers(static_cast<GLFWwindow*>(_data.window));
    }

    void DisplayWindow::PollEvents() {
        glfwPollEvents();
    }

    void DisplayWindow::Destroy() {
        glfwDestroyWindow(static_cast<GLFWwindow*>(_data.window));
        glfwTerminate();
    }
}

#endif

