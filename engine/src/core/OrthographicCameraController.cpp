#include "OrthographicCameraController.h"

#include "Application.h"
#include "DisplayWindow.h"

#include "EventBus.h"
#include "events/MouseScrolledEvent.h"
#include "events/WindowResizedEvent.h"

#include "Input.h"

#include "glm/glm.hpp"

namespace engine {
	void OrthoGraphicCameraController::Init(Application& app) {
		auto window = app.GetWindow();
		const auto& eventBus = window->GetEventBus();

		_aspectRatio = (float)window->GetWidth() / (float)window->GetHeight();

		_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);

		eventBus->Subscribe(this, &OrthoGraphicCameraController::OnMouseScrolled);
		eventBus->Subscribe(this, &OrthoGraphicCameraController::OnWindowResized);
	}

	void OrthoGraphicCameraController::Update(Timestem deltaTime) {
		glm::vec3 cameraPosition = _camera.GetPosition();

		if (Input::IsKeyPressed(EG_KEY_D)) {
			_camera.SetPosition(cameraPosition.x + _cameraMoveSpeed * deltaTime, cameraPosition.y, cameraPosition.z);
		}
		else if (engine::Input::IsKeyPressed(EG_KEY_A)) {
			_camera.SetPosition(cameraPosition.x - _cameraMoveSpeed * deltaTime, cameraPosition.y, cameraPosition.z);
		}

		if (engine::Input::IsKeyPressed(EG_KEY_W)) {
			_camera.SetPosition(cameraPosition.x, cameraPosition.y + _cameraMoveSpeed * deltaTime, cameraPosition.z);
		}
		else if (engine::Input::IsKeyPressed(EG_KEY_S)) {
			_camera.SetPosition(cameraPosition.x, cameraPosition.y - _cameraMoveSpeed * deltaTime, cameraPosition.z);
		}
	}

	void OrthoGraphicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		_zoomLevel -= e.GetY() * _cameraZoomSpeed;
		_zoomLevel = std::max(_zoomLevel, 0.25f);
		_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
	}

	void OrthoGraphicCameraController::OnWindowResized(WindowResizedEvent& e) {
		_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
	}
}