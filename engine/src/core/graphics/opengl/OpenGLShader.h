#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "EngineHeader.h"

#include "../Shader.h"

namespace engine {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader() = default;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void SetUniformInt(const std::string& name, int value);

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformFloat2(const std::string& name, const glm::vec2& vector);
		void SetUniformFloat3(const std::string& name, const glm::vec3& vector);
	
		void SetUniformFloat4(const std::string& name, const glm::vec4& vector);

		void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::unordered_map<unsigned int, std::string> ParseShaders(const std::string& filePath);
		void CompileShader(const std::unordered_map<unsigned int, std::string>& shaders);

		unsigned int GetUniformLocation(const std::string& name);

	private:
		unsigned int _id;

		std::unordered_map<std::string, unsigned int> _uniformLocations;
	};
}

#endif