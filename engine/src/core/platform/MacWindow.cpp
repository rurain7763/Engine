#ifdef PLATFORM_MAC
#include "../DisplayWindow.h"
#include "../Logger.h"

#include "../events/WindowClosedEvent.h"
#include "../events/WindowResizedEvent.h"
#include "../events/KeyPressedEvent.h"
#include "../events/KeyReleasedEvent.h"
#include "../events/MouseButtonPressedEvent.h"
#include "../events/MouseButtonReleasedEvent.h"
#include "../events/MouseMovedEvent.h"
#include "../events/MouseScrolledEvent.h"

#include "../layers/ImGuiLayer.h"
#include "graphics/GraphicsContext.h"
#include "graphics/Shader.h"
#include "graphics/Buffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Renderer.h"
#include "graphics/RenderCommand.h"

#include "GLFW/glfw3.h"

namespace engine {
	DisplayWindow::DisplayWindow() {
		_eventBus = std::make_unique<EventBus>();
		_layerGroup = std::make_unique<LayerGroup>();
	}

	void DisplayWindow::Init(int width, int height, const char* title) {
		EG_ASSERT(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		EG_ASSERT(window != nullptr, "Failed to create window");

		_graphicsContext.reset(GraphicsContext::Create(GraphicsAPI::OpenGL, window));
		_graphicsContext->Init();

		glfwMakeContextCurrent(window);

		glfwSetWindowUserPointer(window, this);

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			DisplayWindow* displayWindow = (DisplayWindow*)glfwGetWindowUserPointer(window);
			displayWindow->GetEventBus()->Publish<WindowClosedEvent>();
		});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			DisplayWindow* displayWindow = (DisplayWindow*)glfwGetWindowUserPointer(window);
			displayWindow->GetEventBus()->Publish<WindowResizedEvent>(width, height);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			DisplayWindow* displayWindow = (DisplayWindow*)glfwGetWindowUserPointer(window);
			switch(action) {
				case GLFW_PRESS:
					displayWindow->GetEventBus()->Publish<KeyPressedEvent>(key);
					break;
				case GLFW_RELEASE:
					displayWindow->GetEventBus()->Publish<KeyReleasedEvent>(key);
					break;
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			DisplayWindow* displayWindow = (DisplayWindow*)glfwGetWindowUserPointer(window);
			switch(action) {
				case GLFW_PRESS:
					displayWindow->GetEventBus()->Publish<MouseButtonPressedEvent>(button);
					break;
				case GLFW_RELEASE:
					displayWindow->GetEventBus()->Publish<MouseButtonReleasedEvent>(button);
					break;
			}
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			DisplayWindow* displayWindow = (DisplayWindow*)glfwGetWindowUserPointer(window);
			displayWindow->GetEventBus()->Publish<MouseMovedEvent>(static_cast<int>(xpos), static_cast<int>(ypos));
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			DisplayWindow* displayWindow = (DisplayWindow*)glfwGetWindowUserPointer(window);
			displayWindow->GetEventBus()->Publish<MouseScrolledEvent>(xoffset, yoffset);
		});

		_window = window;
		_width = width;
		_height = height;
	
		_vertexArray.reset(VertexArray::Create(_graphicsContext.get()));
		_vertexArray->Bind();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
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

			void main() {
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

		_shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);
	}

	void DisplayWindow::Render() {
		auto& renderer = _graphicsContext->GetRenderer();
		auto& renderCommand = _graphicsContext->GetRenderCommand();

		renderCommand->SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		renderCommand->Clear();

		renderer->BeginScene();

		_shader->Bind();
		renderer->Submit(_vertexArray);
		
		renderer->EndScene();

		_layerGroup->Render();

		_graphicsContext->SwapBuffers();
		glfwPollEvents();
	}

	void DisplayWindow::Destroy() {
		GLFWwindow* window = (GLFWwindow*)_window;

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

#endif

