#include "ExampleLayer.h"

#include "imgui/imgui.h"

void ExampleLayer::OnAttach(engine::Application& app) {
    _vertexArray.reset(engine::VertexArray::Create());
    _vertexArray->Bind();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.2f, 1.0f, 0.f, 0.f,
        -0.5f, 0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, 0.f, 1.f,
        0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f, 1.f, 0.f,
        0.5f, 0.5f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f, 1.f, 1.f
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
    //_vertexBuffer.reset();
    //_indexBuffer.reset();
    _camera.reset();
}

void ExampleLayer::OnUpdate(engine::Timestem deltaTime) {
    static glm::vec3 position = glm::vec3(0, 0, 0);
    static glm::vec3 rotation = glm::vec3(0, 0, 0);
    static glm::vec3 scale = glm::vec3(1, 1, 1);

    _camera->Update(deltaTime);

    engine::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    engine::RenderCommand::Clear();

    engine::Renderer::BeginScene(_camera->GetCamera());

    glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::mat4 traslationMat = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));

    auto shader = _shaderLibrary.Get("texture");

    shader->Bind();
    shader->SetFloat3("u_color", _color);
    _texture->Bind(0);
    shader->SetInt("u_texture", 0);
    engine::Renderer::Submit(shader, _vertexArray, traslationMat * rotationMat * scaleMat);

    _alpahTexture->Bind(0);
    shader->SetInt("u_texture", 0);
    engine::Renderer::Submit(shader, _vertexArray, traslationMat * rotationMat * scaleMat);

    engine::Renderer::EndScene();
}

void ExampleLayer::OnGUIUpdate() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Color", &_color.r);
    ImGui::End();
}
