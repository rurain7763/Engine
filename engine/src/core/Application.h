#ifndef APPLICATION_H
#define APPLICATION_H

#include "EngineHeader.h"

namespace engine {
    class DisplayWindow;
    class GraphicsContext;
    class LayerGroup;

    class EG_API Application {
    public:
        Application();
        virtual ~Application() = default;

        void Run();
        void Shutdown();

        inline Ref<DisplayWindow> GetWindow() const { return _window; }
        inline Ref<GraphicsContext> GetGraphicsContext() const { return _graphicsContext; }
        inline Ref<LayerGroup> GetLayerGroup() const { return _layerGroup; }

    private:
        void OnWindowClosed(class WindowClosedEvent& event);
        void OnWindowResize(class WindowResizedEvent& event);

    private:
        bool _running;

        Ref<DisplayWindow> _window;
        Ref<GraphicsContext> _graphicsContext;

        Ref<LayerGroup> _layerGroup;
        int _imGuiLayerID;

        float _lastFrameTime;
    };
};

#endif // APPLICATION_H