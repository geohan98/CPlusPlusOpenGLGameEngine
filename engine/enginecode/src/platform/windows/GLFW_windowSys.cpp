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
#ifdef NG_DEBUG
			LOG_CORE_CRITICAL("FAILED TO INITALIZE GLFW");
#endif // NG_DEBUG
		}
		else
		{
#ifdef NG_DEBUG
			LOG_CORE_WARN("GLFW INITALIZED");
#endif // NG_DEBUG
		}
	}
	void GLFW_WindowSys::stop(SystemSignal close, ...)
	{
#ifdef NG_DEBUG
		LOG_CORE_WARN("TERMINATING GLFW");
#endif // NG_DEBUG
		glfwTerminate();;
	}
}