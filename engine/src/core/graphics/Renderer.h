#ifndef RENDERER_H
#define RENDERER_H

#include "EngineHeader.h"

#include "glm/glm.hpp"

namespace engine {
    class VertexArray;
    class Shader;

    class Renderer {
    public:
        Renderer() = default;
        ~Renderer() = default;
        
        static void BeginScene(class OrthographicCamera& camera);
        static void EndScene();
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

    private:
        static glm::mat4 s_viewProjectionMatrix;
    };
}

#endif
