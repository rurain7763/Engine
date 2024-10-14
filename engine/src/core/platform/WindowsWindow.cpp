#include "pch.h"

#ifdef PLATFORM_WINDOWS
#include "../DisplayWindow.h"
#include "../Logger.h"

namespace engine {
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
	}

	void DisplayWindow::Destroy() {
		GLFWwindow* window = (GLFWwindow*)_window;
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

#endif

