#include "Buffer.h"
#include "Logger.h"

#include "GraphicsContext.h"
#include "GraphicsAPI.h"
#include "opengl/OpenGLBuffer.h"

namespace engine {
	VertexBuffer* VertexBuffer::Create(GraphicsContext* context, const float* vertices, unsigned int count) {
		VertexBuffer* buffer = nullptr;
		switch (context->GetAPI()->GetType()) {
			case GraphicsAPI::Type::OpenGL: buffer = new OpenGLVertexBuffer(); break;
		}

		EG_ASSERT(buffer != nullptr, "Unknown GraphicsAPI");
		buffer->SetData(vertices, count);
		return buffer;
	}

	IndexBuffer* IndexBuffer::Create(GraphicsContext* context, const unsigned int* indices, unsigned int count) {
		IndexBuffer* buffer = nullptr;
		switch (context->GetAPI()->GetType()) {
			case GraphicsAPI::Type::OpenGL: buffer = new OpenGLIndexBuffer(); break;
		}

		EG_ASSERT(buffer != nullptr, "Unknown GraphicsAPI");
		buffer->SetData(indices, count);
		return buffer;
	}
}