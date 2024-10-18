#include "Shader.h"
#include "Logger.h"

#include "GraphicsContext.h"
#include "opengl/OpenGLShader.h"

#include "glad/glad.h"

namespace engine {
	Shader* Shader::Create(const std::string& filePath) {
		switch (GraphicsContext::GetType()) {
		case GraphicsType::OpenGL: return new OpenGLShader(filePath);
		}
		LOG_ERROR("Unsupported Graphics API");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
        switch(GraphicsContext::GetType()) {
			case GraphicsType::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
		}
		LOG_ERROR("Unsupported Graphics API");
		return nullptr;
	}
}
