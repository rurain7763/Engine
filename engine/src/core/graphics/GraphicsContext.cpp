#include "GraphicsContext.h"
#include "Logger.h"
#include "../DisplayWindow.h"

#include "opengl/OpenGLContext.h"

namespace engine {
    GraphicsType GraphicsContext::s_type = GraphicsType::None;

	GraphicsContext* GraphicsContext::Create(GraphicsType type, DisplayWindow* window) {
		switch (type) {
			case GraphicsType::OpenGL: return new OpenGLContext(static_cast<GLFWwindow*>(window->GetNativeWindow()));
            case GraphicsType::None: break;
		}
		EG_ASSERT(false, "Unknown GraphicsAPI");
		return nullptr;
	}
}
