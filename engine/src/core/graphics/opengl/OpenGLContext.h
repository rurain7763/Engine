#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "../GraphicsContext.h"

struct GLFWwindow;

namespace engine {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext() : _nativeWindow(nullptr) {}
		~OpenGLContext() = default;

		virtual void Init(class DisplayWindow* window) override;

	private:
		GLFWwindow* _nativeWindow;
	};
}

#endif 

