#ifndef SANDBOX_H
#define SANDBOX_H

#include "Engine.h"
#include "ExampleLayer.h"

class Sandbox : public engine::Application {
public:
    Sandbox() {
        GetLayerGroup()->AddLayer<ExampleLayer>();
    }
};

#endif // SANDBOX_H
