#include "engine_pch.h"
#include "include/platform/windows/GLFW_windowSys.h"
#include "GLFW/glfw3.h"
#include "systems/Log.h"

namespace Engine
{
	void GLFW_WindowSys::start(SystemSignal init, ...)
	{
		if (!glfwInit())
		{
			LOG_CORE_CRITICAL("FAILED TO INITALIZE GLFW");
		}
		else
		{
			LOG_CORE_WARN("GLFW INITALIZED");
		}
	}
	void GLFW_WindowSys::stop(SystemSignal close, ...)
	{
		LOG_CORE_WARN("TERMINATING GLFW");
		glfwTerminate();;
	}
}