#include "ExampleLayer.h"

#include "imgui/imgui.h"
#include "graphics/opengl/OpenGLShader.h"

void ExampleLayer::OnAttach(engine::Application& app) {
    _vertexArray.reset(engine::VertexArray::Create());
    _vertexArray->Bind();

    float vertices[] = {
        -0.125f, -0.125f, 0.0f, 0.8f, 0.3f, 0.2f, 1.0f, 0.f, 0.f,
        -0.124f, 0.125f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, 0.f, 1.f,
        0.125f, -0.125f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f, 1.f, 0.f,
        0.125f, 0.125f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f, 1.f, 1.f
    };

    _vertexBuffer.reset(engine::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));

    engine::VertexBufferLayout layout;
    layout.Push<float>("aPos", 3);
    layout.Push<float>("aColor", 4);
    layout.Push<float>("aTexCoord", 2);

    _vertexBuffer->SetLayout(layout);
    _vertexArray->AddVertexBuffer(_vertexBuffer);

    unsigned int indices[] = { 0, 1, 2, 1, 3, 2 };
    _indexBuffer.reset(engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
    _vertexArray->SetIndexBuffer(_indexBuffer);

    _texture.reset(engine::Texture2D::Create("assets/images/dog.png"));
    _alpahTexture.reset(engine::Texture2D::Create("assets/images/alpha.png"));
    
    _shaderLibrary.Load("assets/shaders/texture.glsl");

    _camera = std::make_shared<engine::OrthoGraphicCameraController>();
    _camera->Init(app);
}

void ExampleLayer::OnDetach() {
    _vertexArray.reset();
    _vertexBuffer.reset();
    _indexBuffer.reset();
    _camera.reset();
}

void ExampleLayer::OnUpdate(engine::Timestem deltaTime) {
    static glm::vec3 position = glm::vec3(0, 0, 0);
    static glm::vec3 rotation = glm::vec3(0, 0, 0);
    static glm::vec3 scale = glm::vec3(0.25, 0.25, 0.25);

    rotation.z += 50.0f * deltaTime;

    if (engine::Input::IsKeyPressed(EG_KEY_UP)) {
        position.y += 0.5f * deltaTime;
    }
    else if (engine::Input::IsKeyPressed(EG_KEY_DOWN)) {
        position.y -= 0.5f * deltaTime;
    }

    if (engine::Input::IsKeyPressed(EG_KEY_LEFT)) {
        position.x -= 0.5f * deltaTime;
    }
    else if (engine::Input::IsKeyPressed(EG_KEY_RIGHT)) {
        position.x += 0.5f * deltaTime;
    }

    _camera->Update(deltaTime);

    engine::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    engine::RenderCommand::Clear();

    engine::Renderer::BeginScene(_camera->GetCamera());

    glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    auto glShader = std::static_pointer_cast<engine::OpenGLShader>(_shaderLibrary.Get("texture"));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            glm::mat4 traslationMat = glm::translate(glm::mat4(1.0f), glm::vec3(position.x + i * 0.25f * scale.x, position.y + j * 0.25f * scale.y, position.z));

            glShader->Bind();
            glShader->SetUniformFloat3("u_color", _color);
            _texture->Bind(0);
            glShader->SetUniformInt("u_texture", 0);
            engine::Renderer::Submit(glShader, _vertexArray, traslationMat * rotationMat * scaleMat);

            _alpahTexture->Bind(0);
            glShader->SetUniformInt("u_texture", 0);
            engine::Renderer::Submit(glShader, _vertexArray, traslationMat * rotationMat * scaleMat);
        }
    }

    engine::Renderer::EndScene();
}

void ExampleLayer::OnGUIUpdate() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Color", &_color.r);
    ImGui::End();
}
