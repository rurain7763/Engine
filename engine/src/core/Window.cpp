#include "Windows.h"
#include "Logger.h"

namespace engine {
    void Windows::Init(int width, int height, const char* title) {
        if(glfwInit() == GLFW_FALSE) {
            LOG_EG_FATAL("Failed to initialize GLFW");
            EG_ASSERT(false, "Failed to initialize GLFW");
        }

        LOG_EG_INFO("Initialized GLFW");

        _window = glfwCreateWindow(width, height, title, NULL, NULL);
        if(_window == NULL) {
            LOG_EG_FATAL("Failed to create window");
            glfwTerminate();
            EG_ASSERT(false, "Failed to create window");
        }

        LOG_EG_INFO("Created window");

        glfwMakeContextCurrent(_window);
    }

    void Windows::Destroy() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
}