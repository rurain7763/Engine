#ifndef LAYER2D_H
#define LAYER2D_H

#include "Engine.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Layer2D : public engine::Layer {
public:
    virtual void OnAttach(engine::Application& app) override;
    virtual void OnDetach() override;
    virtual void OnUpdate(engine::Timestem deltaTime) override;
    virtual void OnGUIUpdate() override;

private:
    engine::Ref<engine::OrthoGraphicCameraController> _cameraCtrl;
};

#endif