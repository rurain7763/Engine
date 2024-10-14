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

namespace engine {
	DisplayWindow::DisplayWindow() {
		_eventBus = std::make_unique<EventBus>();
		_layerGroup = std::make_unique<LayerGroup>();
	}

	void DisplayWindow::Init(int width, int height, const char* title) {
		if(glfwInit() == GLFW_FALSE) {
			EG_ASSERT(false, "Failed to initialize GLFW");
			return;
		}

		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if(window == nullptr) {
			EG_ASSERT(false, "Failed to create window");
			return;
		}

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
			displayWindow->GetEventBus()->Publish<MouseMovedEvent>(xpos, ypos);
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			DisplayWindow* displayWindow = (DisplayWindow*)glfwGetWindowUserPointer(window);
			displayWindow->GetEventBus()->Publish<MouseScrolledEvent>(
				static_cast<float>(xoffset), 
				static_cast<float>(yoffset)
			);
		});
	}

	void DisplayWindow::Render() {
		glClear(GL_COLOR_BUFFER_BIT);

		_layerGroup->Render();

		glfwSwapBuffers(glfwGetCurrentContext());
		glfwPollEvents();
	}

	void DisplayWindow::Destroy() {
		GLFWwindow* window = (GLFWwindow*)_window;

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

#endif

