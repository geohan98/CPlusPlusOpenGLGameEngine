#include "engine_pch.h"
#include "include/platform/OpenGL/GLFW_windowSys.h"
#include "include/platform/OpenGL/GLFW_windowImp.h"
namespace Engine
{
	void GLFW_WindowSys::start(SystemSignal init, ...)
	{
		m_window = GLFW_WindowImp::create();
	}
	void GLFW_WindowSys::stop(SystemSignal close, ...)
	{
		m_window->close();
	}
}