#ifdef PLATFORM_WINDOWS
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
#include "graphics/opengl/OpenGLContext.h"
#include "graphics/Shader.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace engine {
	DisplayWindow::DisplayWindow() {
		_eventBus = std::make_unique<EventBus>();
		_layerGroup = std::make_unique<LayerGroup>();
	}

	GLuint vao;

	void DisplayWindow::Init(int width, int height, const char* title) {
		EG_ASSERT(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");

		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		EG_ASSERT(window != nullptr, "Failed to create window");

		_graphicsContext = new OpenGLContext(window);
		_graphicsContext->Init();

		glfwMakeContextCurrent(window);

		_window = window;
		_width = width;
		_height = height;

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

		
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		const char* vertexShaderSource = R"(
			#version 330 core

			layout(location = 0) in vec3 aPos;

			void main() {
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core

			out vec4 FragColor;

			void main() {
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			}
		)";

		_shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);

		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void DisplayWindow::Render() {
		glClear(GL_COLOR_BUFFER_BIT);

		_shader->Bind();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		_layerGroup->Render();

		_graphicsContext->SwapBuffers();
		glfwPollEvents();
	}

	void DisplayWindow::Destroy() {
		GLFWwindow* window = (GLFWwindow*)_window;

		delete _graphicsContext;
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

#endif

