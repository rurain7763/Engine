#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

namespace engine {
	class GraphicsContext {
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}

#endif
