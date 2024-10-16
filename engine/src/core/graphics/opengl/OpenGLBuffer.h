#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "../Buffer.h"

namespace engine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer();
		virtual ~OpenGLVertexBuffer();

		virtual void SetData(const float* vertices, unsigned int count) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const VertexBufferLayout& layout) override;
		virtual const VertexBufferLayout& GetLayout() const override;

	private:
		unsigned int _id;
		VertexBufferLayout _layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer();
		virtual ~OpenGLIndexBuffer();

		virtual void SetData(unsigned int* indices, unsigned int count) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual unsigned int GetCount() const override { return _count; }

	private:
		unsigned int _id;
		unsigned int _count;
	};
}

#endif