#include "RenderCommand.h"
#include "GraphicsAPI.h"
#include "GraphicsContext.h"
#include "Logger.h"

#include "opengl/OpenGLGraphicsAPI.h"

namespace engine {
    Ref<GraphicsAPI> RenderCommand::s_api = nullptr;

    void RenderCommand::Init() {
        switch (GraphicsContext::GetType()) {
            case GraphicsType::OpenGL: s_api.reset(new OpenGLGraphicsAPI());
            case GraphicsType::None: break;
        }
        EG_ASSERT(s_api != nullptr, "Unknown GraphicsAPI");
        s_api->Init();
        return;
    }

    void RenderCommand::SetClearColor(float r, float g, float b, float a) {
        s_api->SetClearColor(r, g, b, a);
    }

    void RenderCommand::Clear() {
        s_api->Clear();
    }

    void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray) {
        s_api->DrawIndexed(vertexArray);
    }
}
