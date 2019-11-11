#include "engine_pch.h"
#include "include/platform/OpenGL/GLFW_windowSys.h"
#include "GLFW/glfw3.h"
#include "systems/Log.h"

namespace Engine
{
	void GLFW_WindowSys::start(SystemSignal init, ...)
	{
		if (!glfwInit())
		{
			LOG_CORE_CRITICAL("FAILED TO INITALIZE GLFW");
			return;
		}
		else
		{
			LOG_CORE_INFO("GLFW INITALIZED");
		}
	}
	void GLFW_WindowSys::stop(SystemSignal close, ...)
	{
		LOG_CORE_WARN("TERMINATING GLFW");
		glfwTerminate();;
	}
}