#pragma once
#include "../enginecode/Headers/systems/inputPoller.h"

namespace Engine
{
	namespace Systems {
		/**
		 * GL Vertex Buffer
		 */
		class GLFW_InputPoller : public InputPoller
		{
		protected:
			bool isKeyPressedImp(int keycode) override; ///< Return is a key was pressed in the glfw window
			bool isMouseButtonPressedImp(int keycode) override; ///< return is a mouse button was pressed in the glfw window
			glm::vec2 getMousePositionImp() override; ///< return the mouse position in the glfw window
			float getMouseXImp()override; ///< return the mouse x position in the glfw window
			float getMouseYImp() override; ///< return the mouse y position in the glfw window
		};
	}
}