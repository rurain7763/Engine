#include "OpenGLGraphicsAPI.h"
#include "../VertexArray.h"
#include "../Buffer.h"

#include "glad/glad.h"

namespace engine {
    void OpenGLGraphicsAPI::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);   
    }

    void OpenGLGraphicsAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLGraphicsAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}