#include "Buffer.h"
#include "Logger.h"

#include "GraphicsContext.h"
#include "opengl/OpenGLBuffer.h"

namespace engine {
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int count) {
		VertexBuffer* buffer = nullptr;
		switch (GraphicsContext::GetAPI()) {
			case GraphicsAPI::OpenGL: buffer = new OpenGLVertexBuffer(); break;
		}

		EG_ASSERT(buffer != nullptr, "Unknown GraphicsAPI");
		buffer->SetData(vertices, count);
		return buffer;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count) {
		IndexBuffer* buffer = nullptr;
		switch (GraphicsContext::GetAPI()) {
			case GraphicsAPI::OpenGL: buffer = new OpenGLIndexBuffer(); break;
		}

		EG_ASSERT(buffer != nullptr, "Unknown GraphicsAPI");
		buffer->SetData(indices, count);
		return buffer;
	}
}