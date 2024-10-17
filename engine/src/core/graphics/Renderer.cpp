#include "Renderer.h"
#include "GraphicsAPI.h"
#include "VertexArray.h"
#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace engine {
    void Renderer::BeginScene(OrthographicCamera& camera) {
        // TODO: set camera, light, shader setting etc.
        _viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
        // TODO: batch rendering, etc.
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        shader->SetUniformMat4("u_viewProjection", _viewProjectionMatrix);
        shader->SetUniformMat4("u_transform", transform);

        _renderCommand->DrawIndexed(vertexArray);
    }
}