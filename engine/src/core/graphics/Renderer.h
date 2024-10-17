#ifndef RENDERER_H
#define RENDERER_H

#include "EngineHeader.h"

#include "glm/glm.hpp"

namespace engine {
    class GraphicsAPI;
    class VertexArray;
    class RenderCommand;
    class Shader;

    class Renderer {
    public:
        Renderer(RenderCommand* renderCommand) : _renderCommand(renderCommand) {}

        void BeginScene(class OrthographicCamera& camera);
        void EndScene();

        void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

    private:
        RenderCommand* _renderCommand;

        glm::mat4 _viewProjectionMatrix;
    };
}

#endif