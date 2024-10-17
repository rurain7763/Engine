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

		virtual std::shared_ptr<class Renderer>& GetRenderer() override { return _renderer; }
		virtual std::shared_ptr<class RenderCommand>& GetRenderCommand() override { return _renderCommand; }
		virtual std::shared_ptr<class GraphicsAPI>& GetAPI() override { return _graphicsAPI; }

	private:
		GLFWwindow* _nativeWindow;

		std::shared_ptr<class GraphicsAPI> _graphicsAPI;
		std::shared_ptr<class RenderCommand> _renderCommand;
		std::shared_ptr<class Renderer> _renderer;
	};
}

#endif 

