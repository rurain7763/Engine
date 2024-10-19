#ifndef LAYER_H
#define LAYER_H

#include "EngineHeader.h"
#include "utils/Timestem.h"

const int LAYER_ORDER_MAX = 1000;

namespace engine {
    class EG_API Layer {
    public:
        Layer(const std::string& name = "Layer", int order = 0) {
            _name = name;
            _order = order;
            if(_order > LAYER_ORDER_MAX) {
                _order = LAYER_ORDER_MAX;
            }
        }

        virtual ~Layer() = default;

        virtual void OnAttach(class Application& app) = 0;
        virtual void OnUpdate(Timestem deltaTime) = 0;
        virtual void OnDetach() = 0;
        
        inline const std::string& GetName() const { return _name; }
        inline int GetOrder() const { return _order; }

    private:
        int _order;
        std::string _name;
    };
}

#endif
