#include "GraphicsContext.h"
#include "Logger.h"

#include "opengl/OpenGLContext.h"

namespace engine {
	GraphicsAPI GraphicsContext::s_api = GraphicsAPI::None;

	GraphicsContext* GraphicsContext::Create(GraphicsAPI api, void* nativeWindow) {
		s_api = api;

		switch (api) {
			case GraphicsAPI::OpenGL: return new OpenGLContext(static_cast<GLFWwindow*>(nativeWindow));
		}

		EG_ASSERT(false, "Unknown GraphicsAPI");
		return nullptr;
	}
}