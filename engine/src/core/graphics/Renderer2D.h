#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "EngineHeader.h"

#include "glm/glm.hpp"

namespace engine {
    class OrthographicCamera;
    class Renderer2D {
    public:
        static void Init();
        
        static void BeginScene(class OrthographicCamera& camera);
        static void EndScene();
        
        static void DrawRect(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRect(const glm::vec3& position, const glm::vec2& size, float rotation, const class Texture* texture);
    };
}

#endif
