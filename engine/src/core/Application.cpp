#include "pch.h"
#include "DisplayWindow.h"
#include "Application.h"
#include "Logger.h"
#include "Input.h"
#include "utils/Timestem.h"

#include "EventBus.h"
#include "events/WindowClosedEvent.h"
#include "events/WindowResizedEvent.h"

#include "LayerGroup.h"
#include "layers/ImGuiLayer.h"

#include "graphics/GraphicsContext.h"
#include "graphics/RenderCommand.h"

#include "GLFW/glfw3.h"

namespace engine {
    Application::Application() {
        Logger::Init();

        _window = std::make_shared<DisplayWindow>();
        _window->Init(1280, 720, "Engine");
        _window->GetEventBus()->Subscribe<Application, WindowClosedEvent>(this, &Application::OnWindowClosed);
        _window->GetEventBus()->Subscribe<Application, WindowResizedEvent>(this, &Application::OnWindowResize);

        _graphicsContext.reset(GraphicsContext::Create(GraphicsType::OpenGL, _window.get()));

        Input::Init(_window.get());

        _layerGroup = std::make_shared<LayerGroup>();
        _imGuiLayerID = _layerGroup->AddLayer<ImGuiLayer>();
    }

    void Application::Run() {
        _running = true;
        _windowHidden = false;
        _lastFrameTime = 0.0f;

        for(auto itr = _layerGroup->begin(); itr != _layerGroup->end(); itr++) {
            (*itr)->OnAttach(*this);
        }

        while(_running) {
            float currTime = static_cast<float>(glfwGetTime());
            Timestem deltaTime = currTime - _lastFrameTime;
            if(deltaTime > 0.25f) deltaTime = 0.25f; // clamp deltaTime to 0.25s (4fps)
            _lastFrameTime = currTime;

            ImGuiLayer* imGuiLayer = _layerGroup->GetLayer<ImGuiLayer>(_imGuiLayerID);

            if (!_windowHidden) {
                for (auto itr = _layerGroup->begin(); itr != _layerGroup->end(); itr++) {
                    (*itr)->OnUpdate(deltaTime);
                }
            }

            imGuiLayer->Begin();
            for(auto itr = _layerGroup->begin(); itr != _layerGroup->end(); itr++) {
                (*itr)->OnGUIUpdate();
            }
            imGuiLayer->End();

            _window->Update();
            _window->PollEvents();
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
        const int width = event.GetWidth();
        const int height = event.GetHeight();

        _windowHidden = width == 0 || height == 0;
        if(!_windowHidden) {
            RenderCommand::SetViewport(0, 0, width, height);
		}

		EG_LOG_INFO("Window resized: %dx%d", event.GetWidth(), event.GetHeight());
	} 
}
