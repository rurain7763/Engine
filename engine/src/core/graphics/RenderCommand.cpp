#include "RenderCommand.h"
#include "GraphicsAPI.h"

namespace engine {
    void RenderCommand::SetClearColor(float r, float g, float b, float a) {
        _graphicsAPI->SetClearColor(r, g, b, a);
    }

    void RenderCommand::Clear() {
        _graphicsAPI->Clear();
    }

    void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
        _graphicsAPI->DrawIndexed(vertexArray);
    }
}