#ifndef WINDOWS_H
#define WINDOWS_H

#include "EngineHeader.h"
#include "eventbus/EventBus.h"
#include "layergroup/LayerGroup.h"

namespace engine {
    class EG_API DisplayWindow {
    public:
        DisplayWindow();
        virtual ~DisplayWindow() = default;

        void Init(int width, int height, const char* title);
        void Render();
        void Destroy();

        inline std::unique_ptr<EventBus>& GetEventBus() { return _eventBus; }
        inline std::unique_ptr<LayerGroup>& GetLayerGroup() { return _layerGroup; }

        inline void* GetNativeWindow() const { return _window; }

    private:
        void* _window;
        int _width, _height;

        class GraphicsContext* _graphicsContext;

        std::unique_ptr<EventBus> _eventBus;
        std::unique_ptr<LayerGroup> _layerGroup;
    }; 
}

#endif