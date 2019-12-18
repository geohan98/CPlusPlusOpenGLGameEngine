
#include "systems/inputPoller.h"

namespace Engine
{
	class GLFW_InputPoller : public InputPoller
	{
	protected:
		bool isKeyPressedImp(int keycode) override;
		bool isMouseButtonPressedImp(int keycode) override;
		glm::vec2 getMousePositionImp() override;
		float getMouseXImp()override;
		float getMouseYImp() override;
	};
}