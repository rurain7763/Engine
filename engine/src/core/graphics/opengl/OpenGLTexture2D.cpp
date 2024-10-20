#include "OpenGLTexture2D.h"
#include "Logger.h"

#include "glad/glad.h"
#include "stb_image.h"

namespace engine {
    OpenGLTexture2D::OpenGLTexture2D(unsigned int width, unsigned int height, unsigned int channels) {
        EG_ASSERT(channels == 3 || channels == 4, "Unsupported image format");

        _width = width;
        _height = height;
        _channels = channels;

        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        _id = id;
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        : _path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        EG_ASSERT(data != nullptr, "Failed to load %s image!", path.c_str());
        _width = width;
        _height = height;
        _channels = channels;
        
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        // srcFormat : �ؽ��� �������� ����
        // dstFormat : �ؽ��ķ� ��ȯ�� ����
        GLenum srcFormat = 0, dstFormat = 0;
        if (channels == 4) {
            srcFormat = GL_RGBA8;
			dstFormat = GL_RGBA;
		} else if (channels == 3) {
			srcFormat = GL_RGB;
			dstFormat = GL_RGB;
		} else {
			EG_ASSERT(false, "Unsupported image format");
        }

        glTexImage2D(GL_TEXTURE_2D, 0, srcFormat, _width, _height, 0, dstFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
        
        _id = id;
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &_id);
    }

    void OpenGLTexture2D::Bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    void OpenGLTexture2D::SetData(void* data, unsigned int size) {
        GLenum srcFormat = 0, dstFormat = 0;
        if (_channels == 4) {
            EG_ASSERT(size == _width * _height * 4, "Data must be entire texture!");

            srcFormat = GL_RGBA8;
            dstFormat = GL_RGBA;
        }
        else if (_channels == 3) {
            EG_ASSERT(size == _width * _height * 3, "Data must be entire texture!");

            srcFormat = GL_RGB;
            dstFormat = GL_RGB;
        }

        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(GL_TEXTURE_2D, 0, srcFormat, _width, _height, 0, dstFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}
