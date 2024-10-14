#ifndef INPUT_H
#define INPUT_H

#include "EngineHeader.h"

#include "events/KeyPressedEvent.h"
#include "events/KeyReleasedEvent.h"
#include "events/MouseButtonPressedEvent.h"
#include "events/MouseButtonReleasedEvent.h"
#include "events/MouseMovedEvent.h"
#include "events/MouseScrolledEvent.h"

namespace engine {
	class EG_API Input {
	public:
		static void Init(class DisplayWindow* window);
		static void Destroy();

		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static float GetMouseX();
		static float GetMouseY();
		static float GetMouseScrollX();
		static float GetMouseScrollY();

	private:
		void OnKeyPressed(KeyPressedEvent& event);
		void OnKeyReleased(KeyReleasedEvent& event);

		void OnMouseButtonPressed(MouseButtonPressedEvent& event);
		void OnMouseButtonReleased(MouseButtonReleasedEvent& event);
		void OnMouseMoved(MouseMovedEvent& event);
		void OnMouseScrolled(MouseScrolledEvent& event);

	private:
		static Input* s_instance;

		float _mouseX, _mouseY;
		std::bitset<8> _mouseBit;
		float _mouseScrollX, _mouseScrollY;

		std::bitset<512> _keyBit;
	};
}

#endif
