#ifndef APPLICATION_H
#define APPLICATION_H

#include "EngineHeader.h"

namespace engine {
    class EG_API Application {
    public:
        Application();
        virtual ~Application() = default;

        void Init();
        void Run();
        void Shutdown();

    private:
        void OnWindowClosed(class WindowClosedEvent& event);
        void OnWindowResize(class WindowResizedEvent& event);

    private:
        bool _running;

        std::shared_ptr<class DisplayWindow> _window;
        std::shared_ptr<class GraphicsContext> _graphicsContext;

        std::shared_ptr<class LayerGroup> _layerGroup;

        std::shared_ptr<class VertexArray> _vertexArray;
        std::shared_ptr<class VertexBuffer> _vertexBuffer;
        std::shared_ptr<class IndexBuffer> _indexBuffer;
        std::shared_ptr<class Shader> _shader;
        std::shared_ptr<class OrthographicCamera> _camera;
    };
};

#endif // APPLICATION_H