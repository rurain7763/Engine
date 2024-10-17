#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#include "EngineHeader.h"
#include "GraphicsAPI.h"

namespace engine {
	class GraphicsContext {
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual std::shared_ptr<class Renderer>& GetRenderer() = 0;
		virtual std::shared_ptr<class RenderCommand>& GetRenderCommand() = 0;
		virtual std::shared_ptr<class GraphicsAPI>& GetAPI() = 0;

		static GraphicsContext* Create(GraphicsAPI::Type api, void* nativeWindow);
	};
}

#endif
