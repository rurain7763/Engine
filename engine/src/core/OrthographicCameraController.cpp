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
			cameraPosition.x += _cameraMoveSpeed * deltaTime;
		}
		else if (engine::Input::IsKeyPressed(EG_KEY_A)) {
			cameraPosition.x -= _cameraMoveSpeed * deltaTime;
		}

		if (engine::Input::IsKeyPressed(EG_KEY_W)) {
			cameraPosition.y += _cameraMoveSpeed * deltaTime;
		}
		else if (engine::Input::IsKeyPressed(EG_KEY_S)) {
			cameraPosition.y -= _cameraMoveSpeed * deltaTime;
		}

		_camera.SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);
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