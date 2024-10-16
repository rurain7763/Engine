#ifndef BUFFER_H
#define BUFFER_H

namespace engine {
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, unsigned int count);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual unsigned int GetCount() const = 0;

		static IndexBuffer* Create(unsigned int* indices, unsigned int count);
	};
}	

#endif