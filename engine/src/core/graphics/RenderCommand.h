#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "EngineHeader.h"

namespace engine {
    class VertexArray;

    class RenderCommand {
    public:
        RenderCommand() = default;
        ~RenderCommand() = default;

        static void Init();

        static void SetViewport(int x, int y, int width, int height);
        static void SetClearColor(float r, float g, float b, float a);
        static void Clear();

        static void DrawIndexed(const Ref<VertexArray>& vertexArray);

    private:
        static Ref<class GraphicsAPI> s_api;
    };
}

#endif
