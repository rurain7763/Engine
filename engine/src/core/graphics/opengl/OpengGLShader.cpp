#include "OpengGLShader.h"
#include "Logger.h"

#include "glad/glad.h"

namespace engine {
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {
		// Create an empty vertex OpenGLShader handle
		GLuint vertexOpenGLShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex OpenGLShader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexOpenGLShader, 1, &source, 0);

		// Compile the vertex OpenGLShader
		glCompileShader(vertexOpenGLShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexOpenGLShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexOpenGLShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::string infoLog;
			infoLog.resize(maxLength);
			glGetShaderInfoLog(vertexOpenGLShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the OpenGLShader anymore.
			glDeleteShader(vertexOpenGLShader);

			EG_ASSERT(false, "Vertex OpenGLShader compilation failed: %s", infoLog.c_str());
			return;
		}

		// Create an empty fragment OpenGLShader handle
		GLuint fragmentOpenGLShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment OpenGLShader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentOpenGLShader, 1, &source, 0);

		// Compile the fragment OpenGLShader
		glCompileShader(fragmentOpenGLShader);

		glGetShaderiv(fragmentOpenGLShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentOpenGLShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::string infoLog;
			infoLog.resize(maxLength);
			glGetShaderInfoLog(fragmentOpenGLShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the OpenGLShader anymore.
			glDeleteShader(fragmentOpenGLShader);
			// Either of them. Don't leak OpenGLShaders.
			glDeleteShader(vertexOpenGLShader);

			EG_ASSERT(false, "Fragment OpenGLShader compilation failed: %s", infoLog.c_str());
			return;
		}

		// Vertex and fragment OpenGLShaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// Attach our OpenGLShaders to our program
		glAttachShader(program, vertexOpenGLShader);
		glAttachShader(program, fragmentOpenGLShader);

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
			glDeleteShader(vertexOpenGLShader);
			glDeleteShader(fragmentOpenGLShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Always detach OpenGLShaders after a successful link.
		glDetachShader(program, vertexOpenGLShader);
		glDetachShader(program, fragmentOpenGLShader);

		_id = program;
	}

	void OpenGLShader::Bind() const {
		glUseProgram(_id);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
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