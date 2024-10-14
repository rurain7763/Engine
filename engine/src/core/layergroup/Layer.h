#ifndef LAYER_H
#define LAYER_H

#include "EngineHeader.h"

const int LAYER_ORDER_MAX = 1000;

class EG_API Layer {
public:
    Layer(const std::string& name = "Layer", int order = 0) : _order(min(order, LAYER_ORDER_MAX)), _name(name) {}
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnRender() {}
    
    inline const std::string& GetName() const { return _name; }
    inline int GetOrder() const { return _order; }

private:
    int _order;
    std::string _name;
};

#endif