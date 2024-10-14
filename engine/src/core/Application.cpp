#include "pch.h"
#include "Application.h"
#include "Logger.h"

#include "input/Input.h"

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
        _window->GetLayerGroup()->AddLayer<ImGuiLayer>(_window.get());

        Input::Init(_window.get());

        _running = true;
    }

    void Application::Run() {
        while(_running) {
            // TODO: Update
            _window->Render();
        }
    }

    void Application::Shutdown() {
        Input::Destroy();
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
}