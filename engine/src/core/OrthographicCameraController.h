#ifndef ORTHOGRPAPHIC_CAMERA_CONTROLLER_H
#define ORTHOGRPAPHIC_CAMERA_CONTROLLER_H

#include "EngineHeader.h"
#include "graphics/OrthographicCamera.h"
#include "utils/Timestem.h"

namespace engine {
	class OrthoGraphicCameraController {
	public:
		OrthoGraphicCameraController() = default;
		~OrthoGraphicCameraController() = default;

		void Init(class Application& app);
		void Update(Timestem deltaTime);

		OrthographicCamera& GetCamera() { return _camera; }
		const OrthographicCamera& GetCamera() const { return _camera; }

	private:
		void OnMouseScrolled(class MouseScrolledEvent& e);
		void OnWindowResized(class WindowResizedEvent& e);

	private:
		OrthographicCamera _camera;

		float _aspectRatio = 0.0f;

		float _zoomLevel = 1.0f;

		float _cameraMoveSpeed = 5.0f;
		float _cameraZoomSpeed = 0.25f;
	};
}

#endif