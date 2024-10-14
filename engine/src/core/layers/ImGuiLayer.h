#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "EngineHeader.h"
#include "../layergroup/Layer.h"

namespace engine {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer(class DisplayWindow* window);
		~ImGuiLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnRender() override;

	private:
		void* _nativeWindow;
	};
}

#endif 

