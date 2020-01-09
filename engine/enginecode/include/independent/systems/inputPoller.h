#pragma once
#include <glm/glm.hpp>

namespace Engine
{
	/**
	 * Input Poller, allows key input detection and boolean returns
	 */
	class InputPoller
	{
	private:
		static std::unique_ptr<InputPoller> s_instance;																	///<  singleton instance
	protected:
		virtual bool isKeyPressedImp(int keycode) = 0;																	///< check if a key is pressed
		virtual bool isMouseButtonPressedImp(int button) = 0;															///< check if a moue button is pressed
		virtual glm::vec2 getMousePositionImp() = 0;																	///< get mouse position
		virtual float getMouseXImp() = 0;																				///< get mouse position x
		virtual float getMouseYImp() = 0;																				///< get mouse position Y
	public:
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImp(keycode); }					///< check if a key is pressed
		inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImp(button); }		///< check if a moue button is pressed
		inline static glm::vec2 getMousePosition() { return s_instance->getMousePositionImp(); }						///< get mouse position
		inline static float getMouseX() { return s_instance->getMouseXImp(); }											///< get mouse position x
		inline static float getMouseY() { return s_instance->getMouseYImp(); }											///< get mouse position Y
	};
}