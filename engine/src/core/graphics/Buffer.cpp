#include "Buffer.h"
#include "Logger.h"

#include "GraphicsContext.h"
#include "opengl/OpenGLBuffer.h"

namespace engine {
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int count) {
		switch (GraphicsContext::GetAPI()) {
			case GraphicsAPI::OpenGL: return new OpenGLVertexBuffer(vertices, count);
		}

		EG_ASSERT(false, "Unknown GraphicsAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count) {
		switch (GraphicsContext::GetAPI()) {
			case GraphicsAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		EG_ASSERT(false, "Unknown GraphicsAPI");
		return nullptr;
	}
}