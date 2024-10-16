#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace engine {
	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader() = default;

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int _id;
	};
}

#endif

