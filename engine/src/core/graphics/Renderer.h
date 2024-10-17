#ifndef RENDERER_H
#define RENDERER_H

#include "EngineHeader.h"

namespace engine {
    class GraphicsAPI;
    class VertexArray;
    class RenderCommand;

    class Renderer {
    public:
        Renderer(RenderCommand* renderCommand) : _renderCommand(renderCommand) {}

        void BeginScene();
        void EndScene();

        void Submit(const std::shared_ptr<VertexArray>& vertexArray);

    private:
        RenderCommand* _renderCommand;
    };
}

#endif