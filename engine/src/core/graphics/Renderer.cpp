#include "Renderer.h"
#include "GraphicsAPI.h"
#include "VertexArray.h"
#include "RenderCommand.h"

namespace engine {
    void Renderer::BeginScene() {
        // TODO: set camera, light, shader setting etc.
    }

    void Renderer::EndScene() {
        // TODO: batch rendering, etc.
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
        _renderCommand->DrawIndexed(vertexArray);
    }
}