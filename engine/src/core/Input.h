#ifndef INPUT_H
#define INPUT_H

#include "EngineHeader.h"
#include "KeyCodes.h"
#include "MouseButtons.h"

namespace engine {
	class EG_API Input {
	public:
		static void Init(class DisplayWindow* window);
		static void Destroy();

		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static int GetMouseX();
		static int GetMouseY();
		static double GetMouseScrollX();
		static double GetMouseScrollY();

	private:
		void OnKeyPressed(class KeyPressedEvent& event);
		void OnKeyReleased(class KeyReleasedEvent& event);

		void OnMouseButtonPressed(class MouseButtonPressedEvent& event);
		void OnMouseButtonReleased(class MouseButtonReleasedEvent& event);
		void OnMouseMoved(class MouseMovedEvent& event);
		void OnMouseScrolled(class MouseScrolledEvent& event);

	private:
		static Input* s_instance;

		int _mouseX, _mouseY;
		std::bitset<8> _mouseBit;
		double _mouseScrollX, _mouseScrollY;

		std::bitset<512> _keyBit;
	};
}

#endif
