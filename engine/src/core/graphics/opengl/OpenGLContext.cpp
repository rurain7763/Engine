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
		
        s_type = GraphicsType::OpenGL;
        
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EG_ASSERT(status, "Failed to initialize Glad!");

		EG_LOG_INFO("OpenGL Info:");
		EG_LOG_INFO("  Vendor: %s", glGetString(GL_VENDOR));
		EG_LOG_INFO("  Renderer: %s", glGetString(GL_RENDERER));
		EG_LOG_INFO("  Version: %s", glGetString(GL_VERSION));

        RenderCommand::Init();
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(_nativeWindow);
	}
}
