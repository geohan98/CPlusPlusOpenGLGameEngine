#include "engine_pch.h"
#include "include/platform/windows/GLFW_inputPoller.h"
#include <GLFW/glfw3.h>
#include "core/application.h"
#include "systems/ButtonCodes.h"

namespace Engine
{
	namespace Systems {
		std::unique_ptr<InputPoller> InputPoller::s_instance = std::unique_ptr<InputPoller>(new GLFW_InputPoller);

		bool GLFW_InputPoller::isKeyPressedImp(int keycode)
		{
			GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
			int result = glfwGetKey(window, keycode);
			return result == KEY_PRESS || result == KEY_REPEAT;
		}

		bool GLFW_InputPoller::isMouseButtonPressedImp(int button)
		{
			GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
			int result = glfwGetMouseButton(window, button);
			return result == KEY_PRESS;
		}

		glm::vec2 GLFW_InputPoller::getMousePositionImp()
		{
			GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			return glm::vec2(x, y);
		}

		float GLFW_InputPoller::getMouseXImp()
		{
			return getMousePositionImp().x;
		}

		float GLFW_InputPoller::getMouseYImp()
		{
			return getMousePositionImp().y;
		}
	}
}