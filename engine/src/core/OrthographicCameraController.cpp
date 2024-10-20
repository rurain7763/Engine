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
		glm::vec3 dir = { 0.0f, 0.0f, 0.0f };

		if (Input::IsKeyPressed(EG_KEY_D)) {
			dir.x = 1.0f;
		}
		else if (engine::Input::IsKeyPressed(EG_KEY_A)) {
			dir.x = -1.0f;
		}

		if (engine::Input::IsKeyPressed(EG_KEY_W)) {
			dir.y = 1.0f;
		}
		else if (engine::Input::IsKeyPressed(EG_KEY_S)) {
			dir.y = -1.0f;
		}

		if (dir.x != 0.0f || dir.y != 0.0f) {
			dir = glm::normalize(dir) * (_cameraMoveSpeed * deltaTime);
		}

		glm::vec3 cameraPosition = _camera.GetPosition() + dir;
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