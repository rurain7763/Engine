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
    std::shared_ptr<engine::GraphicsContext> _graphicsContext;

    std::shared_ptr<engine::VertexArray> _vertexArray;
    std::shared_ptr<engine::VertexBuffer> _vertexBuffer;
    std::shared_ptr<engine::IndexBuffer> _indexBuffer;
    std::shared_ptr<engine::Shader> _shader;
    std::shared_ptr<engine::OrthographicCamera> _camera;

    glm::vec3 _color;
};

#endif