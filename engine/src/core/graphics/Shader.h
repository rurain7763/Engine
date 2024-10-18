#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glm/glm.hpp"

namespace engine {
	class Shader {
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		static Shader* Create(const std::string& filePath);
	};
}

#endif

