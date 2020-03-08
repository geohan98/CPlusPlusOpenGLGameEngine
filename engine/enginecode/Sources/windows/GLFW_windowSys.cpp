#include "engine_pch.h"
#include "../enginecode/Headers/windows/GLFW_windowSys.h"
#include "GLFW/glfw3.h"
#include "../enginecode/Headers/systems/Log.h"

namespace Engine
{
	void Systems::GLFW_WindowSys::start(SystemSignal init, ...)
	{
		LOG_CORE_WARN("[SYSTEMS][GLFW WINDOW][GLFW WINDOW STARTED]");
		if (!glfwInit())
		{
#ifdef NG_DEBUG
			LOG_CORE_CRITICAL("[SYSTEMS][GLFW WINDOW][FAILED TO INITALIZE GLFW]");
#endif // NG_DEBUG
		}
		else
		{
#ifdef NG_DEBUG
			LOG_CORE_WARN("[SYSTEMS][GLFW WINDOW][GLFW INITALIZED]");
#endif // NG_DEBUG
		}
	}
	void Systems::GLFW_WindowSys::stop(SystemSignal close, ...)
	{
#ifdef NG_DEBUG
		LOG_CORE_WARN("[SYSTEMS][GLFW WINDOW][TERMINATING GLFW]");
#endif // NG_DEBUG
		glfwTerminate();;
		LOG_CORE_WARN("[SYSTEMS][GLFW WINDOW][GLFW WINDOW STOPPED]");
	}
}