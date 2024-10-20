#ifndef EXAMPLE_LAYER_H
#define EXAMPLE_LAYER_H

#include "Engine.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ExampleLayer : public engine::Layer {
public:
    virtual void OnAttach(engine::Application& app) override;
    virtual void OnDetach() override;
    virtual void OnUpdate(engine::Timestem deltaTime) override;
    virtual void OnGUIUpdate() override;

private:
    engine::ShaderLibrary _shaderLibrary;
    engine::Ref<engine::OrthoGraphicCameraController> _camera;

    engine::Ref<engine::VertexArray> _vertexArray;
    engine::Ref<engine::VertexBuffer> _vertexBuffer;
    engine::Ref<engine::IndexBuffer> _indexBuffer;
    engine::Ref<engine::Texture> _texture, _alpahTexture;

    glm::vec3 _color = glm::vec3(1.0);
};

#endif
