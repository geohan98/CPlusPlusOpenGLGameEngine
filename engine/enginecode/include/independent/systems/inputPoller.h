#pragma once
#include <glm/glm.hpp>

namespace Engine
{
	class InputPoller
	{
	private:
		static std::unique_ptr<InputPoller> s_instance;
	protected:
		virtual bool isKeyPressedImp(int keycode) = 0;
		virtual bool isMouseButtonPressedImp(int button) = 0;
		virtual glm::vec2 getMousePositionImp() = 0;
		virtual float getMouseXImp() = 0;
		virtual float getMouseYImp() = 0;
	public:
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImp(keycode); }
		inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImp(button); }
		inline static glm::vec2 getMousePosition() { return s_instance->getMousePositionImp(); }
		inline static float getMouseX() { return s_instance->getMouseXImp(); }
		inline static float getMouseY() { return s_instance->getMouseYImp(); }
	};
}