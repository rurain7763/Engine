#ifndef EXAMPLE_LAYER_H
#define EXAMPLE_LAYER_H

#include "Engine.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

class ExampleLayer : public engine::Layer {
public:
    virtual void OnAttach(engine::Application& app) override;
    virtual void OnDetach() override;
    virtual void OnUpdate(engine::Timestep deltaTime) override;

private:
    engine::Ref<engine::VertexArray> _vertexArray;
    engine::Ref<engine::VertexBuffer> _vertexBuffer;
    engine::Ref<engine::IndexBuffer> _indexBuffer;
    engine::Ref<engine::Shader> _shader;
    engine::Ref<engine::OrthographicCamera> _camera;
    engine::Ref<engine::Texture> _texture;

    glm::vec3 _color;
};

#endif
