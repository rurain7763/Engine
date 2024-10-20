#include "Texture.h"
#include "Logger.h"

#include "GraphicsContext.h"
#include "GraphicsAPI.h"
#include "opengl/OpenGLTexture2D.h"

namespace engine {
    Texture2D* Texture2D::Create(unsigned int width, unsigned int height, unsigned int channels) {
        switch (GraphicsContext::GetType()) {
        case GraphicsType::OpenGL: return new OpenGLTexture2D(width, height, channels);
        case GraphicsType::None: break;
        }
        EG_ASSERT(false, "Unsupported Graphics API");
        return nullptr;
    }

    Texture2D* Texture2D::Create(const std::string& path) {
        switch(GraphicsContext::GetType()) {
            case GraphicsType::OpenGL: return new OpenGLTexture2D(path);
            case GraphicsType::None: break;
        }
        EG_ASSERT(false, "Unsupported Graphics API");
        return nullptr;
    }
}
