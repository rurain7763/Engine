#ifndef SHADER_H
#define SHADER_H

#include "EngineHeader.h"

#include "glm/glm.hpp"

namespace engine {
	class Shader {
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;

		static Shader* Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static Shader* Create(const std::string& filePath);
		static Shader* Create(const std::string& name, const std::string& filePath);
	};

	class ShaderLibrary {
	public:
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		Ref<Shader> Get(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> _shaders;
	};
}

#endif

