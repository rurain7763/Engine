#ifndef SANDBOX_H
#define SANDBOX_H

#include "Engine.h"

#include <memory>

class ExampleLayer : public engine::Layer {
public:
    virtual void OnAttach(engine::Application& app) override {
        _graphicsContext = app.GetGraphicsContext();

        _vertexArray.reset(engine::VertexArray::Create(_graphicsContext.get()));
		_vertexArray->Bind();

		float vertices[] = {
			 0, 0, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0, 600, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 800, 0, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		};

		_vertexBuffer.reset(engine::VertexBuffer::Create(_graphicsContext.get(), vertices, sizeof(vertices) / sizeof(float)));

		engine::VertexBufferLayout layout;
		layout.Push<float>("aPos", 3);
		layout.Push<float>("aColor", 4);

		_vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(_vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		_indexBuffer.reset(engine::IndexBuffer::Create(_graphicsContext.get(), indices, sizeof(indices) / sizeof(unsigned int)));
		_vertexArray->SetIndexBuffer(_indexBuffer);

		const char* vertexShaderSource = R"(
			#version 330 core

			layout(location = 0) in vec3 aPos;
			layout(location = 1) in vec4 aColor;
			layout(location = 2) in vec2 aTexCoord;

			out vec4 vertexColor;

            uniform mat4 u_viewProjection;

			void main() {
				gl_Position = u_viewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
				vertexColor = aColor;
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core

			out vec4 FragColor;

			in vec4 vertexColor;

			void main() {
				FragColor = vec4(vertexColor);
			}
		)";

		_shader = std::make_shared<engine::Shader>(vertexShaderSource, fragmentShaderSource);

        _camera = std::make_shared<engine::OrthographicCamera>();
        _camera->SetProjection(800, 600);
    }

    virtual void OnDetach() override {
        _vertexArray.reset();
        _vertexBuffer.reset();
        _indexBuffer.reset();
        _shader.reset();
        _camera.reset();
    }

    virtual void OnUpdate() override {
        glm::vec3 cameraPosition = _camera->GetPosition();

        if(engine::Input::IsKeyPressed(EG_KEY_RIGHT)) {
            _camera->SetPosition(cameraPosition.x + 1, cameraPosition.y, cameraPosition.z);
        } else if(engine::Input::IsKeyPressed(EG_KEY_LEFT)) {
            _camera->SetPosition(cameraPosition.x - 1, cameraPosition.y, cameraPosition.z);
        }

        if(engine::Input::IsKeyPressed(EG_KEY_UP)) {
            _camera->SetPosition(cameraPosition.x, cameraPosition.y + 1, cameraPosition.z);
        } else if(engine::Input::IsKeyPressed(EG_KEY_DOWN)) {
            _camera->SetPosition(cameraPosition.x, cameraPosition.y - 1, cameraPosition.z);
        }

        auto& renderer = _graphicsContext->GetRenderer();
        auto& renderCommand = _graphicsContext->GetRenderCommand();

        renderCommand->SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        renderCommand->Clear();

        renderer->BeginScene(*_camera.get());

        renderer->Submit(_shader, _vertexArray);
        
        renderer->EndScene();
    }

private:
    std::shared_ptr<engine::GraphicsContext> _graphicsContext;

    std::shared_ptr<engine::VertexArray> _vertexArray;
    std::shared_ptr<engine::VertexBuffer> _vertexBuffer;
    std::shared_ptr<engine::IndexBuffer> _indexBuffer;
    std::shared_ptr<engine::Shader> _shader;
    std::shared_ptr<engine::OrthographicCamera> _camera;
};

class Sandbox : public engine::Application {
public:
    Sandbox() {
        GetLayerGroup()->AddLayer<ExampleLayer>();
    }
};

#endif // SANDBOX_H