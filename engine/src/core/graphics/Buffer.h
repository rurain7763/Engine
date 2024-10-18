#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>

namespace engine {
    class GraphicsContext;

    enum DataType {
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4, Bool
    };

    class VertexBufferLayout {
    public:
        struct Element {
            std::string name;
            DataType type;
            unsigned int typeSize;
            unsigned int count;
            bool normalized;
        };

    public:
        template<typename T>
        void Push(const std::string& name, int count, bool normalized = false);

        template<>
        void Push<float>(const std::string& name, int count, bool normalized) {
            Element element;
            element.name = name;
            element.type = DataType::Float;
            element.typeSize = static_cast<unsigned int>(sizeof(float));
            element.count = static_cast<unsigned int>(count);
            element.normalized = normalized;

            _elements.push_back(element);
            _stride += sizeof(float) * count;
        }

        // Add more Push functions for other data types

        inline int GetStride() const { return _stride; }
        inline const std::vector<Element>& GetElements() const { return _elements; }

        std::vector<Element>::iterator begin() { return _elements.begin(); }
        std::vector<Element>::iterator end() { return _elements.end(); }
        std::vector<Element>::const_iterator begin() const { return _elements.begin(); }
        std::vector<Element>::const_iterator end() const { return _elements.end(); }

    private:
        std::vector<Element> _elements;
        int _stride = 0;
    };

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

        virtual void SetData(const float* data, unsigned int count) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

        virtual void SetLayout(const VertexBufferLayout& layout) = 0;
        virtual const VertexBufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(const float* vertices, unsigned int count);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

        virtual void SetData(const unsigned int* indices, unsigned int count) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual unsigned int GetCount() const = 0;

		static IndexBuffer* Create(const unsigned int* indices, unsigned int count);
	};
}	

#endif
