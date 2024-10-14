#include "pch.h"
#include "Application.h"
#include "Logger.h"

#include "eventbus/EventBus.h"
#include "layers/ImGuiLayer.h"

namespace engine {
    Application::Application() {
        _running = false;

        Logger::init();

        _window = std::make_unique<DisplayWindow>();
    }

    Application::~Application() {
        
    }

    void Application::Init() {
        _window->Init(800, 600, "Engine");
        _window->GetEventBus()->Subscribe<Application, WindowClosedEvent>(this, &Application::OnWindowClosed);
        _window->GetEventBus()->Subscribe<Application, WindowResizedEvent>(this, &Application::OnWindowResize);
        _window->GetEventBus()->Subscribe<Application, KeyPressedEvent>(this, &Application::OnKeyPressed);
        _window->GetEventBus()->Subscribe<Application, KeyReleasedEvent>(this, &Application::OnKeyReleased);
        _window->GetEventBus()->Subscribe<Application, MouseButtonPressedEvent>(this, &Application::OnMouseButtonPressed);
        _window->GetEventBus()->Subscribe<Application, MouseButtonReleasedEvent>(this, &Application::OnMouseButtonReleased);
        _window->GetEventBus()->Subscribe<Application, MouseMovedEvent>(this, &Application::OnMouseMoved);
        _window->GetEventBus()->Subscribe<Application, MouseScrolledEvent>(this, &Application::OnMouseScrolled);

        _window->GetLayerGroup()->AddLayer<ImGuiLayer>(_window.get());

        _running = true;
    }

    void Application::Run() {
        while(_running) {
            // TODO: Process events
            // TODO: Update
            _window->Render();
        }
    }

    void Application::Shutdown() {
        _window->Destroy();

        _running = false;
    }

    void Application::OnWindowClosed(WindowClosedEvent& event) {
        _running = false;
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