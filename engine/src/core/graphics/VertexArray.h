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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}

#endif
