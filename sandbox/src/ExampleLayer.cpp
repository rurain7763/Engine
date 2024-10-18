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
    
    const char* vertexShaderSource = R"(
			#version 330 core

			layout(location = 0) in vec3 aPos;
			layout(location = 1) in vec4 aColor;
			layout(location = 2) in vec2 aTexCoord;

			out vec4 vertexColor;
            out vec2 texCoord;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

			void main() {
				gl_Position = u_viewProjection * u_transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
				vertexColor = aColor;
                texCoord = aTexCoord;
			}
		)";

    const char* fragmentShaderSource = R"(
			#version 330 core

			out vec4 FragColor;

			in vec4 vertexColor;
            in vec2 texCoord;
  
            uniform sampler2D u_texture;
            uniform vec3 u_color;
  
			void main() {
				FragColor = texture(u_texture, 1.0);
			}
		)";

    _shader.reset(engine::Shader::Create(vertexShaderSource, fragmentShaderSource));

    _camera = std::make_shared<engine::OrthographicCamera>();
    _camera->SetProjection(-0.4, 0.4, -0.3, 0.3);
}

void ExampleLayer::OnDetach() {
    _vertexArray.reset();
    _vertexBuffer.reset();
    _indexBuffer.reset();
    _shader.reset();
    _camera.reset();
}

void ExampleLayer::OnUpdate(engine::Timestep deltaTime) {
    glm::vec3 cameraPosition = _camera->GetPosition();

    if (engine::Input::IsKeyPressed(EG_KEY_RIGHT)) {
        _camera->SetPosition(cameraPosition.x + 0.5f * deltaTime, cameraPosition.y, cameraPosition.z);
    }
    else if (engine::Input::IsKeyPressed(EG_KEY_LEFT)) {
        _camera->SetPosition(cameraPosition.x - 0.5f * deltaTime, cameraPosition.y, cameraPosition.z);
    }

    if (engine::Input::IsKeyPressed(EG_KEY_UP)) {
        _camera->SetPosition(cameraPosition.x, cameraPosition.y + 0.5f * deltaTime, cameraPosition.z);
    }
    else if (engine::Input::IsKeyPressed(EG_KEY_DOWN)) {
        _camera->SetPosition(cameraPosition.x, cameraPosition.y - 0.5f * deltaTime, cameraPosition.z);
    }

    static glm::vec3 position = glm::vec3(0, 0, 0);
    static glm::vec3 rotation = glm::vec3(0, 0, 0);
    static glm::vec3 scale = glm::vec3(0.25, 0.25, 0.25);

    rotation.z += 50.0f * deltaTime;

    if (engine::Input::IsKeyPressed(EG_KEY_W)) {
        position.y += 0.5f * deltaTime;
    }
    else if (engine::Input::IsKeyPressed(EG_KEY_S)) {
        position.y -= 0.5f * deltaTime;
    }

    if (engine::Input::IsKeyPressed(EG_KEY_A)) {
        position.x -= 0.5f * deltaTime;
    }
    else if (engine::Input::IsKeyPressed(EG_KEY_D)) {
        position.x += 0.5f * deltaTime;
    }

    engine::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    engine::RenderCommand::Clear();

    engine::Renderer::BeginScene(*_camera.get());

    glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    auto glShader = std::static_pointer_cast<engine::OpenGLShader>(_shader);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            glm::mat4 traslationMat = glm::translate(glm::mat4(1.0f), glm::vec3(position.x + i * 0.25f * scale.x, position.y + j * 0.25f * scale.y, position.z));

            glShader->Bind();
            glShader->SetUniformFloat3("u_color", _color);
            _texture->Bind(0);
            glShader->SetUniformInt("u_texture", 0);
            engine::Renderer::Submit(_shader, _vertexArray, traslationMat * rotationMat * scaleMat);
        }
    }

    engine::Renderer::EndScene();

    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Color", &_color.r);
    ImGui::End();
}
