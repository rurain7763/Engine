#ifndef OPENGL_GRAPHICS_API_H
#define OPENGL_GRAPHICS_API_H

#include "../GraphicsAPI.h"

namespace engine {
    class OpenGLGraphicsAPI : public GraphicsAPI {
    public:
        virtual void SetClearColor(float r, float g, float b, float a) override;
        virtual void Clear() override;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}

#endif
