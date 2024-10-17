#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "EngineHeader.h"

namespace engine {
	class GraphicsContext;
	class VertexBuffer;
	class IndexBuffer;

	class VertexArray {
	public:
		VertexArray() = default;
		virtual ~VertexArray() = default;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create(GraphicsContext* context);
	};
}

#endif