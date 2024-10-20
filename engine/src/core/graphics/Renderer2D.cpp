#include "Renderer2D.h"

#include "Shader.h"
#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Texture.h"
#include "RenderCommand.h"

#include "glm/gtc/matrix_transform.hpp"

namespace engine {
    ShaderLibrary shaderLibrary;

    Ref<VertexArray> vertexArray;
    Ref<VertexBuffer> vertexBuffer;
    Ref<IndexBuffer> indexBuffer;

    void Renderer2D::Init() {
        vertexArray.reset(VertexArray::Create());
        vertexArray->Bind();

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.f, 0.f,
            -0.5f, 0.5f, 0.0f, 0.f, 1.f,
            0.5f, -0.5f, 0.0f, 1.f, 0.f,
            0.5f, 0.5f, 0.0f, 1.f, 1.f
        };

        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));

        engine::VertexBufferLayout layout;
        layout.Push<float>("position", 3);
        layout.Push<float>("texCoord", 2);

        vertexBuffer->SetLayout(layout);
        vertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[] = { 0, 1, 2, 1, 3, 2 };
        indexBuffer.reset(engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
        vertexArray->SetIndexBuffer(indexBuffer);

        shaderLibrary.Load("assets/shaders/flatcolor.glsl");
        shaderLibrary.Load("assets/shaders/texture.glsl");
    }

    void Renderer2D::BeginScene(OrthographicCamera &camera) {
        auto shader = shaderLibrary.Get("flatcolor");
        shader->Bind();
        shader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());

        shader = shaderLibrary.Get("texture");
        shader->Bind();
        shader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {
        
    }

    void Renderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
        vertexArray->Bind();
        
        auto shader = shaderLibrary.Get("flatcolor");
        shader->Bind();
        shader->SetFloat4("uColor", color);

        glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        shader->SetMat4("uTransform", translation * rotationMat * scale);

        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, float rotation, const Texture* texture) {
        vertexArray->Bind();

        auto shader = shaderLibrary.Get("texture");
        shader->Bind();

        glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        shader->SetMat4("uTransform", translation * rotationMat * scale);

        texture->Bind(0);
        shader->SetInt("uTexture", 0);

        RenderCommand::DrawIndexed(vertexArray);
    }
}
