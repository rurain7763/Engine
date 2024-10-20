#include "Renderer2D.h"

#include "Shader.h"
#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Texture.h"
#include "RenderCommand.h"

#include "glm/gtc/matrix_transform.hpp"

namespace engine {
    static Ref<VertexArray> vertexArray;
    static Ref<VertexBuffer> vertexBuffer;
    static Ref<IndexBuffer> indexBuffer;

    static Ref<Shader> textureShader;
    static Ref<Texture2D> whiteTexture;

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

        textureShader.reset(Shader::Create("assets/shaders/texture.glsl"));
        whiteTexture.reset(Texture2D::Create(1, 1, 4));
        unsigned int whiteTextureData[] = { 0xffffffff };
        whiteTexture->SetData(whiteTextureData, sizeof(whiteTextureData));
    }

    void Renderer2D::BeginScene(OrthographicCamera &camera) {
        textureShader->Bind();
        textureShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {
        
    }

    void Renderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
        vertexArray->Bind();

        glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        textureShader->SetMat4("uTransform", translation * rotationMat * scale);

        whiteTexture->Bind(0);
        textureShader->SetInt("uTexture", 0);

        textureShader->SetFloat4("uColor", color);

        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, float rotation, const Texture* texture) {
        vertexArray->Bind();

        glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        textureShader->SetMat4("uTransform", translation * rotationMat * scale);

        texture->Bind(0);
        textureShader->SetInt("uTexture", 0);

        textureShader->SetFloat4("uColor", glm::vec4(1.0f));

        RenderCommand::DrawIndexed(vertexArray);
    }
}
