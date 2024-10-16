#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace engine {
	OpenGLVertexBuffer::OpenGLVertexBuffer() {
		glGenBuffers(1, &_id);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &_id);
	}

	void OpenGLVertexBuffer::SetData(const float* vertices, unsigned int count) {
		glBindBuffer(GL_ARRAY_BUFFER, _id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, GL_STATIC_DRAW);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, _id);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const VertexBufferLayout& layout) {
		_layout = layout;
	}

	const VertexBufferLayout& OpenGLVertexBuffer::GetLayout() const {
		return _layout;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer() {
		glGenBuffers(1, &_id);
		_count = 0;
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &_id);
	}

	void OpenGLIndexBuffer::SetData(unsigned int* indices, unsigned int count) {
		_count = count;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_STATIC_DRAW);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}