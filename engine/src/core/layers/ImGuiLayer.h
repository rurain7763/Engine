#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "EngineHeader.h"
#include "../layergroup/Layer.h"

namespace engine {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		virtual void OnAttach(class Application& app) override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep deltaTime) override;

		void Begin();
		void End();

	private:
		void* _nativeWindow;
	};
}

#endif 

