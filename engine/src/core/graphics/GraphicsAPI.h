#ifndef GRAPHICS_API_H
#define GRAPHICS_API_H

#include "EngineHeader.h"

namespace engine {
    class VertexArray;
    
    class GraphicsAPI {
    public:     
        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
    };
}

#endif
