#include "GraphicsContext.h"
#include "Logger.h"
#include "../DisplayWindow.h"

#include "opengl/OpenGLContext.h"

namespace engine {
	GraphicsContext* GraphicsContext::Create(GraphicsAPI::Type api, DisplayWindow* window) {
		switch (api) {
			case GraphicsAPI::Type::OpenGL: return new OpenGLContext(static_cast<GLFWwindow*>(window->GetNativeWindow()));
		}

		EG_ASSERT(false, "Unknown GraphicsAPI");
		return nullptr;
	}
}