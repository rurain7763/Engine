#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "../Buffer.h"

namespace engine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int count);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const VertexBufferLayout& layout) override;
		virtual const VertexBufferLayout& GetLayoutGroup() const override;

	private:
		unsigned int _id;
		VertexBufferLayout _layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual unsigned int GetCount() const override { return _count; }

	private:
		unsigned int _id;
		unsigned int _count;
	};
}

#endif