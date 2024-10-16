#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include "EngineHeader.h"
#include "../VertexArray.h"

namespace engine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return _indexBuffer; }

	private:
		unsigned int _id;

		std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
		std::shared_ptr<IndexBuffer> _indexBuffer;
	};
}

#endif
