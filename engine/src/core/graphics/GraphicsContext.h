#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

namespace engine {
	enum GraphicsAPI {
		None = 0,
		OpenGL = 1
	};

	class GraphicsContext {
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static GraphicsContext* Create(GraphicsAPI api, void* nativeWindow);

		static inline GraphicsAPI GetAPI() { return s_api; }

	protected:
		static GraphicsAPI s_api;
	};
}

#endif
