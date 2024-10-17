#include "VertexArray.h"
#include "Logger.h"

#include "GraphicsContext.h"
#include "opengl/OpenGLVertexArray.h"

namespace engine {
	VertexArray* VertexArray::Create(GraphicsContext* context) {
		switch (context->GetAPI()->GetType()) {
			case GraphicsAPI::OpenGL: return new OpenGLVertexArray();
		}

		EG_ASSERT(false, "Unknown GraphicsAPI");
		return nullptr;
	}
}