#include "OpenGLShader.h"
#include "Logger.h"

#include "glad/glad.h"

namespace engine {
	OpenGLShader::OpenGLShader(const std::string& filePath) {
		auto shaders = ParseShaders(filePath);
		CompileShader(shaders);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {
		std::unordered_map<unsigned int, std::string> shaders;
		shaders[GL_VERTEX_SHADER] = vertexSource;
		shaders[GL_FRAGMENT_SHADER] = fragmentSource;
		CompileShader(shaders);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(_id);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::ParseShaders(const std::string& filePath) {
		std::unordered_map<unsigned int, std::string> shaders;

		std::ifstream file(filePath, std::ifstream::binary);
		if (file.is_open()) {
			unsigned int currentType = GL_INVALID_INDEX;

			std::string line;
			while (std::getline(file, line)) {
				if (line.find("#type") != std::string::npos) {
					if (line.find("vertex") != std::string::npos) {
						currentType = GL_VERTEX_SHADER;
					} 
					else if (line.find("fragment") != std::string::npos || line.find("pixel") != std::string::npos) {
						currentType = GL_FRAGMENT_SHADER;
					}
					else {
						EG_LOG_WARN("Unsupported shader type");
						currentType = GL_INVALID_INDEX;
					}
				}
				else if (currentType != GL_INVALID_INDEX) {
					shaders[currentType].append(line + '\n');
				}
			}

			file.close();
		}
		else {
			EG_LOG_ERROR("Failed to open file: %s", filePath.c_str());
		}

		return shaders;
	}

	void OpenGLShader::CompileShader(const std::unordered_map<unsigned int, std::string>& shaders) {
		GLuint program = glCreateProgram();
		std::vector<GLuint> compiledShaderIDs(shaders.size());

		int index = 0;
		for (const auto& pair : shaders) {
			GLenum shaderType = pair.first;
			GLuint shader = glCreateShader(shaderType);

			const GLchar* source = (const GLchar*)pair.second.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::string infoLog;
				infoLog.resize(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the OpenGLShader anymore.
				glDeleteShader(shader);

				EG_ASSERT(false, "shader compilation failed: %s", infoLog.c_str());
				break;
			}

			glAttachShader(program, shader);
			compiledShaderIDs[index++] = shader;
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetOpenGLShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak OpenGLShaders either.
			for (auto id : compiledShaderIDs) {
				glDeleteShader(id);
			}

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Always detach OpenGLShaders after a successful link.
		for (auto id : compiledShaderIDs) {
			glDetachShader(program, id);
		}	

		_id = program;
	}

	unsigned int OpenGLShader::GetUniformLocation(const std::string& name) {
		if (_uniformLocations.find(name) != _uniformLocations.end()) {
			return _uniformLocations[name];
		}

		GLint location = glGetUniformLocation(_id, name.c_str());
		_uniformLocations[name] = location;
		return location;
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value) {
		GLint location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniformFloat(const std::string& name, float value) {
		GLint location = GetUniformLocation(name);
		glUniform1f(location, value);
	}

	void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& vector) {
		GLint location = GetUniformLocation(name);
		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& vector) {
		GLint location = GetUniformLocation(name);
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& vector) {
		GLint location = GetUniformLocation(name);
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = GetUniformLocation(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}
}