#include "pch.h"

#ifdef PLATFORM_MAC
#include "../DisplayWindow.h"
#include "../Logger.h"
#include "../events/KeyPressedEvent.h"

namespace engine {
	DisplayWindow::DisplayWindow() {
		_eventBus = std::make_unique<EventBus>();
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

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			DisplayWindow* diplayWindow = (DisplayWindow*)window;
			EG_ASSERT(diplayWindow->GetEventBus() != nullptr, "DisplayWindow is null");
			diplayWindow->GetEventBus()->Publish<KeyPressedEvent>(key);
		});
	}

	void DisplayWindow::Destroy() {
		GLFWwindow* window = (GLFWwindow*)_window;
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

#endif

