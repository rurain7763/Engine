#ifndef SANDBOX_H
#define SANDBOX_H

#include "Engine.h"

#include "ExampleLayer.h"
#include "Layer2D.h"

class Sandbox : public engine::Application {
public:
    Sandbox() {
        //GetLayerGroup()->AddLayer<ExampleLayer>();
        GetLayerGroup()->AddLayer<Layer2D>();
    }
};

#endif // SANDBOX_H
