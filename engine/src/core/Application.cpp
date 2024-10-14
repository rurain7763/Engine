#include "pch.h"
#include "Application.h"
#include "Logger.h"
#include "eventbus/EventBus.h"

namespace engine {
    Application::Application() {
        Logger::init();
        LOG_EG_INFO("Created application");

        _window = std::make_unique<DisplayWindow>();
        _window->Init(800, 600, "Engine");

        _window->GetEventBus()->Subscribe<Application, KeyPressedEvent>(this, &Application::OnKeyPressed);
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

    void Application::OnKeyPressed(KeyPressedEvent& event) {
        LOG_EG_INFO("Key pressed: {0}", event.GetKey());
    }
}