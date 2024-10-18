#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "EngineHeader.h"

namespace engine {
    class GraphicsAPI;
    class VertexArray;

    class RenderCommand {
    public:
        RenderCommand(GraphicsAPI* graphicsAPI) : _graphicsAPI(graphicsAPI) {}
        ~RenderCommand() = default;

        void SetClearColor(float r, float g, float b, float a);
        void Clear();

        void DrawIndexed(const Ref<VertexArray>& vertexArray);

    private:
        GraphicsAPI* _graphicsAPI;
    };
}

#endif