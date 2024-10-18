#include "VertexArray.h"
#include "Logger.h"

#include "GraphicsContext.h"
#include "opengl/OpenGLVertexArray.h"

namespace engine {
	VertexArray* VertexArray::Create() {
        switch (GraphicsContext::GetType()) {
            case GraphicsType::OpenGL: return new OpenGLVertexArray();
            case GraphicsType::None: break;
		}

		EG_ASSERT(false, "Unknown GraphicsAPI");
		return nullptr;
	}
}
