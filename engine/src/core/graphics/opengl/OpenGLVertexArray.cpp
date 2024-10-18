#include "OpenGLVertexArray.h"
#include "Logger.h"

#include "glad/glad.h"
#include "OpenGLBuffer.h"

namespace engine {
	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &_id);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		EG_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");

		glBindVertexArray(_id);
		vertexBuffer->Bind();

		int i = 0;
		int offset = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(i);

			GLenum type = GL_FLOAT;
			switch (element.type) {
				case DataType::Float: type = GL_FLOAT;	break;
				case DataType::Int: type = GL_INT;		break;
				case DataType::Int2: type = GL_INT;		break;
				case DataType::Int3: type = GL_INT;		break;
				// Add more cases for other data types
			}

			glVertexAttribPointer(
				i,
				element.count,
				type,
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)offset
			);

			offset += element.typeSize * element.count;
			i++;
		}

		_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(_id);
		indexBuffer->Bind();

		_indexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(_id);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}
}

