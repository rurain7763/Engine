#include "Shader.h"
#include "Logger.h"

#include "GraphicsContext.h"
#include "opengl/OpenGLShader.h"

#include "glad/glad.h"

namespace engine {
	Shader* Shader::Create(GraphicsContext* context, const std::string& vertexSource, const std::string& fragmentSource) {
		switch(context->GetAPI()->GetType()) {
			case GraphicsAPI::Type::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
		}
		LOG_ERROR("Unsupported Graphics API");
		return nullptr;
	}
}