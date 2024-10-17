#include "GraphicsContext.h"
#include "Logger.h"

#include "opengl/OpenGLContext.h"

namespace engine {
	GraphicsContext* GraphicsContext::Create(GraphicsAPI::Type api, void* nativeWindow) {
		switch (api) {
			case GraphicsAPI::Type::OpenGL: return new OpenGLContext(static_cast<GLFWwindow*>(nativeWindow));
		}

		EG_ASSERT(false, "Unknown GraphicsAPI");
		return nullptr;
	}
}