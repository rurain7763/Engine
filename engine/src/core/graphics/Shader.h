#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glm/glm.hpp"

namespace engine {
	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader() = default;

		void Bind() const;
		void Unbind() const;

		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int _id;
	};
}

#endif

