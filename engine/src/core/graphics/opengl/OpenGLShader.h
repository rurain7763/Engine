#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "EngineHeader.h"

#include "../Shader.h"

namespace engine {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& filePath, const std::string& name);
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource, const std::string& name);
		virtual ~OpenGLShader() = default;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vector) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		virtual const std::string& GetName() const override { return _name; }

	private:
		std::unordered_map<unsigned int, std::string> ParseShaders(const std::string& filePath);
		void CompileShader(const std::unordered_map<unsigned int, std::string>& shaders);

		unsigned int GetUniformLocation(const std::string& name);

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformFloat2(const std::string& name, const glm::vec2& vector);

		void SetUniformFloat4(const std::string& name, const glm::vec4& vector);

		void SetUniformMat3(const std::string& name, const glm::mat3& matrix);

	private:
		unsigned int _id;
		std::string _name;

		std::unordered_map<std::string, unsigned int> _uniformLocations;
	};
}

#endif