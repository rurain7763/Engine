#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "EngineHeader.h"
#include "Layer.h"

namespace engine {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		virtual void OnAttach(class Application& app) override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestem deltaTime) override;
		virtual void OnGUIUpdate() override;

		void Begin();
		void End();

	private:
		void* _nativeWindow;
	};
}

#endif 

