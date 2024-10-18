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

	private:
		GLFWwindow* _nativeWindow;
	};
}

#endif 

