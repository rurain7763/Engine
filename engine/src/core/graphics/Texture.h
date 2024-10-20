#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace engine {
    class Texture {
    public:
        Texture() = default;
        virtual ~Texture() = default;
        
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        
        virtual void Bind(unsigned int slot) const = 0;
    };

    class Texture2D : public Texture {
    public:
        Texture2D() = default;
        virtual ~Texture2D() = default;
        
        virtual void SetData(void* data, unsigned int size) = 0;

        static Texture2D* Create(unsigned int width, unsigned int height, unsigned int channels = 4);
        static Texture2D* Create(const std::string& path);
    };
}

#endif
