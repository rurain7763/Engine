#include "pch.h"
#include "Application.h"
#include "Logger.h"

#include "eventbus/EventBus.h"
#include "events/WindowClosedEvent.h"
#include "events/WindowResizedEvent.h"
#include "events/KeyPressedEvent.h"
#include "events/KeyReleasedEvent.h"
#include "events/MouseButtonPressedEvent.h"
#include "events/MouseButtonReleasedEvent.h"
#include "events/MouseMovedEvent.h"
#include "events/MouseScrolledEvent.h"

namespace engine {
    Application::Application() {
        Logger::init();
        LOG_EG_INFO("Created application");

        _window = std::make_unique<DisplayWindow>();
        _window->Init(800, 600, "Engine");
        _window->GetEventBus()->Subscribe<Application, WindowClosedEvent>(this, &Application::OnWindowClosed);
        _window->GetEventBus()->Subscribe<Application, WindowResizedEvent>(this, &Application::OnWindowResize);
        _window->GetEventBus()->Subscribe<Application, KeyPressedEvent>(this, &Application::OnKeyPressed);
        _window->GetEventBus()->Subscribe<Application, KeyReleasedEvent>(this, &Application::OnKeyReleased);
        _window->GetEventBus()->Subscribe<Application, MouseButtonPressedEvent>(this, &Application::OnMouseButtonPressed);
        _window->GetEventBus()->Subscribe<Application, MouseButtonReleasedEvent>(this, &Application::OnMouseButtonReleased);
		_window->GetEventBus()->Subscribe<Application, MouseMovedEvent>(this, &Application::OnMouseMoved);
		_window->GetEventBus()->Subscribe<Application, MouseScrolledEvent>(this, &Application::OnMouseScrolled);
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

    void Application::OnWindowClosed(WindowClosedEvent& event) {
		LOG_EG_INFO("Window closed");
	}

    void Application::OnWindowResize(WindowResizedEvent& event) {
		LOG_EG_INFO("Window resized: {0}x{1}", event.GetX(), event.GetY());
	}

    void Application::OnKeyPressed(KeyPressedEvent& event) {
        LOG_EG_INFO("Key pressed: {0}", event.GetKey());
    }

    void Application::OnKeyReleased(KeyReleasedEvent& event) {
		LOG_EG_INFO("Key released: {0}", event.GetKey());
	}

    void Application::OnMouseButtonPressed(MouseButtonPressedEvent& event) {
        LOG_EG_INFO("Mouse button pressed: {0}", event.GetKey());
    }

    void Application::OnMouseButtonReleased(MouseButtonReleasedEvent& event) {
        LOG_EG_INFO("Mouse button released: {0}", event.GetKey());
    }

    void Application::OnMouseMoved(MouseMovedEvent& event) {
        LOG_EG_INFO("Mouse moved: {0}, {1}", event.GetX(), event.GetY());
    }

    void Application::OnMouseScrolled(MouseScrolledEvent& event) {
        LOG_EG_INFO("Mouse scrolled: {0}, {1}", event.GetX(), event.GetY());
    }
}