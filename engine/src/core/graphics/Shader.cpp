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

	Shader* Shader::Create(const std::string& name, const std::string& filePath) {
		switch (GraphicsContext::GetType()) {
		case GraphicsType::OpenGL: return new OpenGLShader(name, filePath);
		}
		LOG_ERROR("Unsupported Graphics API");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
        switch(GraphicsContext::GetType()) {
			case GraphicsType::OpenGL: return new OpenGLShader(name, vertexSource, fragmentSource);
		}
		LOG_ERROR("Unsupported Graphics API");
		return nullptr;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath) {
		EG_ASSERT(_shaders.find(filePath) == _shaders.end(), "Shader name duplicated!");
		auto shader = Shader::Create(filePath);
		_shaders.emplace(shader->GetName(), shader);
		return _shaders[shader->GetName()];
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath) {
		EG_ASSERT(_shaders.find(name) == _shaders.end(), "Shader name duplicated!");
		auto shader = Shader::Create(name, filePath);
		_shaders.emplace(shader->GetName(), shader);
		return _shaders[shader->GetName()];
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
		EG_ASSERT(_shaders.find(name) == _shaders.end(), "Shader name duplicated!");
		auto shader = Shader::Create(name, vertexSource, fragmentSource);
		_shaders.emplace(shader->GetName(), shader);
		return _shaders[shader->GetName()];
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) const {
		EG_ASSERT(_shaders.find(name) != _shaders.end(), "Shader not found");
		return _shaders.at(name);
	}
}
