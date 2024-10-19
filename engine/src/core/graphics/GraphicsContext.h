#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#include "EngineHeader.h"

namespace engine {
    enum GraphicsType {
        None = 0, OpenGL
    };

	class GraphicsContext {
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

		virtual void Init(class DisplayWindow* window) = 0;

        static GraphicsType GetType() { return s_type; }
        static GraphicsContext* Create(GraphicsType type, class DisplayWindow* window);
        
    protected:
        static GraphicsType s_type;
        
        static Ref<class Renderer> _renderer;
        static Ref<class RenderCommand> _renderCommand;
        static Ref<class GraphicsAPI> _api;
	};
}

#endif
