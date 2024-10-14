#include "Application.h"
#include "Logger.h"

namespace engine {
    GLFWwindow* window;

    Application::Application() {
        Logger::init();
        LOG_EG_INFO("Created application");

        _window = std::make_unique<Windows>();
        _window->Init(800, 600, "Engine");
    }

    Application::~Application() {
        _window->Destroy();
    }

    void Application::Run() {
        while(!glfwWindowShouldClose(glfwGetCurrentContext())) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(glfwGetCurrentContext());
            glfwPollEvents();
        }
    }
}