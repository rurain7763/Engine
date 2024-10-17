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
#include "graphics/Shader.h"
#include "graphics/Buffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Renderer.h"
#include "graphics/RenderCommand.h"

#include "graphics/OrthographicCamera.h"

namespace engine {
    Application::Application() {
        _running = false;
        Logger::Init();

        _window = std::make_shared<DisplayWindow>();
        _layerGroup = std::make_shared<LayerGroup>();
    }

    void Application::Init() {
        _window->Init(800, 600, "Engine");
        _window->GetEventBus()->Subscribe<Application, WindowClosedEvent>(this, &Application::OnWindowClosed);
        _window->GetEventBus()->Subscribe<Application, WindowResizedEvent>(this, &Application::OnWindowResize);
        
        Input::Init(_window.get());

        _graphicsContext.reset(GraphicsContext::Create(GraphicsAPI::OpenGL, _window.get()));
		_graphicsContext->Init();

        _vertexArray.reset(VertexArray::Create(_graphicsContext.get()));
		_vertexArray->Bind();

		float vertices[] = {
			 0, 0, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0, 600, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 800, 0, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		};

		_vertexBuffer.reset(VertexBuffer::Create(_graphicsContext.get(), vertices, sizeof(vertices) / sizeof(float)));

		VertexBufferLayout layout;
		layout.Push<float>("aPos", 3);
		layout.Push<float>("aColor", 4);

		_vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(_vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		_indexBuffer.reset(IndexBuffer::Create(_graphicsContext.get(), indices, sizeof(indices) / sizeof(unsigned int)));
		_vertexArray->SetIndexBuffer(_indexBuffer);

		const char* vertexShaderSource = R"(
			#version 330 core

			layout(location = 0) in vec3 aPos;
			layout(location = 1) in vec4 aColor;
			layout(location = 2) in vec2 aTexCoord;

			out vec4 vertexColor;

            uniform mat4 u_viewProjection;

			void main() {
				gl_Position = u_viewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
				vertexColor = aColor;
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core

			out vec4 FragColor;

			in vec4 vertexColor;

			void main() {
				FragColor = vec4(vertexColor);
			}
		)";

		_shader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource);

        _camera = std::make_shared<OrthographicCamera>();
        _camera->SetProjection(800, 600);

        _layerGroup->AddLayer<ImGuiLayer>(_window.get());

        _running = true;
    }

    void Application::Run() {
        auto& renderer = _graphicsContext->GetRenderer();
        auto& renderCommand = _graphicsContext->GetRenderCommand();

        while(_running) {
            // TODO: Update
            glm::vec3 cameraPosition = _camera->GetPosition();
            
            if(Input::IsKeyPressed(EG_KEY_RIGHT)) {
                _camera->SetPosition(cameraPosition.x + 1, cameraPosition.y, cameraPosition.z);
            } else if(Input::IsKeyPressed(EG_KEY_LEFT)) {
                _camera->SetPosition(cameraPosition.x - 1, cameraPosition.y, cameraPosition.z);
            }

            if(Input::IsKeyPressed(EG_KEY_UP)) {
                _camera->SetPosition(cameraPosition.x, cameraPosition.y + 1, cameraPosition.z);
            } else if(Input::IsKeyPressed(EG_KEY_DOWN)) {
                _camera->SetPosition(cameraPosition.x, cameraPosition.y - 1, cameraPosition.z);
            }

            renderCommand->SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            renderCommand->Clear();

            renderer->BeginScene(*_camera.get());

            renderer->Submit(_shader, _vertexArray);
            
            renderer->EndScene();

            _layerGroup->Render();

            _graphicsContext->SwapBuffers();

            _window->Update();
        }
    }

    void Application::Shutdown() {
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
        _camera->SetProjection(event.GetX(), event.GetY());
	} 
}