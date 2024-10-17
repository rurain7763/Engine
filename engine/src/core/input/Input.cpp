#include "Input.h"

#include "../DisplayWindow.h"

#include "../eventbus/EventBus.h"
#include "events/KeyPressedEvent.h"
#include "events/KeyReleasedEvent.h"
#include "events/MouseButtonPressedEvent.h"
#include "events/MouseButtonReleasedEvent.h"
#include "events/MouseMovedEvent.h"
#include "events/MouseScrolledEvent.h"

namespace engine {
	Input* Input::s_instance = nullptr;

	void Input::Init(DisplayWindow* window) {
		if (s_instance) return;

		s_instance = new Input();

		window->GetEventBus()->Subscribe<Input, KeyPressedEvent>(s_instance, &Input::OnKeyPressed);
		window->GetEventBus()->Subscribe<Input, KeyReleasedEvent>(s_instance, &Input::OnKeyReleased);
		window->GetEventBus()->Subscribe<Input, MouseButtonPressedEvent>(s_instance, &Input::OnMouseButtonPressed);
		window->GetEventBus()->Subscribe<Input, MouseButtonReleasedEvent>(s_instance, &Input::OnMouseButtonReleased);
		window->GetEventBus()->Subscribe<Input, MouseMovedEvent>(s_instance, &Input::OnMouseMoved);
		window->GetEventBus()->Subscribe<Input, MouseScrolledEvent>(s_instance, &Input::OnMouseScrolled);
	}

	void Input::Destroy() {
		if (!s_instance) return;

		delete s_instance;
		s_instance = nullptr;
	}

	bool Input::IsKeyPressed(int keycode) {
		return s_instance->_keyBit.test(keycode);
	}

	bool Input::IsMouseButtonPressed(int button) {
		return s_instance->_mouseBit.test(button);
	}

	int Input::GetMouseX() {
		return s_instance->_mouseX;
	}

	int Input::GetMouseY() {
		return s_instance->_mouseY;
	}

	double Input::GetMouseScrollX() {
		return s_instance->_mouseScrollX;
	}

	double Input::GetMouseScrollY() {
		return s_instance->_mouseScrollY;
	}

	void Input::OnKeyPressed(KeyPressedEvent& event) {
		_keyBit.set(event.GetKey(), true);
	}

	void Input::OnKeyReleased(KeyReleasedEvent& event) {
		_keyBit.set(event.GetKey(), false);
	}

	void Input::OnMouseButtonPressed(MouseButtonPressedEvent& event) {
		_mouseBit.set(event.GetKey(), true);
	}

	void Input::OnMouseButtonReleased(MouseButtonReleasedEvent& event) {
		_mouseBit.set(event.GetKey(), false);
	}

	void Input::OnMouseMoved(MouseMovedEvent& event) {
		_mouseX = event.GetX();
		_mouseY = event.GetY();
	}

	void Input::OnMouseScrolled(MouseScrolledEvent& event) {
		_mouseScrollX = event.GetX();
		_mouseScrollY = event.GetY();
	}
}
