#include "OpenGLContext.h"
#include "OpenGLGraphicsAPI.h"
#include "../RenderCommand.h"
#include "../Renderer.h"

#include "Logger.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace engine {
	OpenGLContext::OpenGLContext(GLFWwindow* nativeWindow)
		: _nativeWindow(nativeWindow)
	{
		EG_ASSERT(nativeWindow != nullptr, "Window is null");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(_nativeWindow);
		
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EG_ASSERT(status, "Failed to initialize Glad!");

		EG_LOG_INFO("OpenGL Info:");
		EG_LOG_INFO("  Vendor: %s", glGetString(GL_VENDOR));
		EG_LOG_INFO("  Renderer: %s", glGetString(GL_RENDERER));
		EG_LOG_INFO("  Version: %s", glGetString(GL_VERSION));

		_graphicsAPI = std::make_shared<OpenGLGraphicsAPI>();
		_renderCommand = std::make_shared<RenderCommand>(_graphicsAPI.get());
		_renderer = std::make_shared<Renderer>(_renderCommand.get());
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(_nativeWindow);
	}
}
