#include "OpenGLGraphicsAPI.h"
#include "../VertexArray.h"
#include "../Buffer.h"

#include "glad/glad.h"

namespace engine {
    void OpenGLGraphicsAPI::Init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
	}

    void OpenGLGraphicsAPI::SetViewport(int x, int y, int width, int height) {
		glViewport(x, y, width, height);
	}

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