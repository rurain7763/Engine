#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "../GraphicsContext.h"

struct GLFWwindow;

namespace engine {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* nativeWindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;

		virtual Ref<class Renderer>& GetRenderer() override { return _renderer; }
		virtual Ref<class RenderCommand>& GetRenderCommand() override { return _renderCommand; }
		virtual Ref<class GraphicsAPI>& GetAPI() override { return _graphicsAPI; }

	private:
		GLFWwindow* _nativeWindow;

		Ref<class GraphicsAPI> _graphicsAPI;
		Ref<class RenderCommand> _renderCommand;
		Ref<class Renderer> _renderer;
	};
}

#endif 

