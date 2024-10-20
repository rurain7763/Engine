#ifndef OPENGL_TEXTURE_2D
#define OPENGL_TEXTURE_2D

#include "../Texture.h"

#include <string>

namespace engine {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(unsigned int width, unsigned int height, unsigned int channels);
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D();
        
        virtual unsigned int GetWidth() const override { return _width; }
        virtual unsigned int GetHeight() const override { return _height; }
        
        virtual void Bind(unsigned int slot) const override;

        virtual void SetData(void* data, unsigned int size) override;
    
    private:
        unsigned int _width, _height;
        unsigned int _channels;
        std::string _path;
        unsigned int _id;
    };
}

#endif
