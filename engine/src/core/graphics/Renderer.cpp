#include "Renderer.h"
#include "GraphicsAPI.h"
#include "VertexArray.h"
#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

#include "opengl/OpenGLShader.h"

namespace engine {
    glm::mat4 Renderer::s_viewProjectionMatrix = glm::mat4(1.0);

    void Renderer::BeginScene(OrthographicCamera& camera) {
        // TODO: set camera, light, shader setting etc.
        s_viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
        // TODO: batch rendering, etc.
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        // this is a temporary solution
        auto glShader = std::static_pointer_cast<OpenGLShader>(shader);

        glShader->Bind();
        glShader->SetMat4("u_viewProjection", s_viewProjectionMatrix);
        glShader->SetMat4("u_transform", transform);

        RenderCommand::DrawIndexed(vertexArray);
    }
}
