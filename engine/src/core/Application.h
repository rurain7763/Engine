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

        inline std::shared_ptr<DisplayWindow> GetWindow() const { return _window; }
        inline std::shared_ptr<GraphicsContext> GetGraphicsContext() const { return _graphicsContext; }
        inline std::shared_ptr<LayerGroup> GetLayerGroup() const { return _layerGroup; }

    private:
        void OnWindowClosed(class WindowClosedEvent& event);
        void OnWindowResize(class WindowResizedEvent& event);

    private:
        bool _running;

        std::shared_ptr<DisplayWindow> _window;
        std::shared_ptr<GraphicsContext> _graphicsContext;

        std::shared_ptr<LayerGroup> _layerGroup;
        int _imGuiLayerID;

        float _lastFrameTime;
    };
};

#endif // APPLICATION_H