#include "GraphicsContext.h"
#include "Logger.h"
#include "DisplayWindow.h"

#include "opengl/OpenGLContext.h"

namespace engine {
    GraphicsType GraphicsContext::s_type = GraphicsType::None;

	GraphicsContext* GraphicsContext::Create(GraphicsType type, DisplayWindow* window) {
		GraphicsContext* ret = nullptr;
		switch (type) {
			case GraphicsType::OpenGL: ret = new OpenGLContext(); break;
            case GraphicsType::None: break;
		}
		EG_ASSERT(ret != nullptr, "Unknown GraphicsAPI");
		ret->Init(window);
		return ret;
	}
}
