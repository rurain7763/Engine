#include "pch.h"
#include "DisplayWindow.h"
#include "Application.h"
#include "Logger.h"
#include "input/Input.h"
#include "input/KeyCodes.h"

#include "eventbus/EventBus.h"
#include "events/WindowClosedEvent.h"
#include "events/WindowResizedEvent.h"

#include "layergroup/LayerGroup.h"
#include "layers/ImGuiLayer.h"

#include "graphics/GraphicsContext.h"

namespace engine {
    Application::Application() {
        Logger::Init();

        _window = std::make_shared<DisplayWindow>();
        _window->Init(800, 600, "Engine");
        _window->GetEventBus()->Subscribe<Application, WindowClosedEvent>(this, &Application::OnWindowClosed);
        _window->GetEventBus()->Subscribe<Application, WindowResizedEvent>(this, &Application::OnWindowResize);

        _graphicsContext.reset(GraphicsContext::Create(GraphicsAPI::Type::OpenGL, _window.get()));
        _graphicsContext->Init();

        Input::Init(_window.get());

        _layerGroup = std::make_shared<LayerGroup>();
        _layerGroup->AddLayer<ImGuiLayer>();
    }

    void Application::Run() {
        _running = true;

        for(auto itr = _layerGroup->begin(); itr != _layerGroup->end(); itr++) {
            (*itr)->OnAttach(*this);
        }

        while(_running) {
            for(auto itr = _layerGroup->begin(); itr != _layerGroup->end(); itr++) {
                (*itr)->OnUpdate();
            }
            _graphicsContext->SwapBuffers();
            _window->Update();
        }
    }

    void Application::Shutdown() {
        for(auto itr = _layerGroup->begin(); itr != _layerGroup->end(); itr++) {
            (*itr)->OnDetach();
        }
        _layerGroup->Destroy();

        Input::Destroy();
        _window->Destroy();

        _running = false;
    }

    void Application::OnWindowClosed(WindowClosedEvent& event) {
        _running = false;
		EG_LOG_INFO("Window closed");
	}

    void Application::OnWindowResize(WindowResizedEvent& event) {
		EG_LOG_INFO("Window resized: %dx%d", event.GetX(), event.GetY());
	} 
}