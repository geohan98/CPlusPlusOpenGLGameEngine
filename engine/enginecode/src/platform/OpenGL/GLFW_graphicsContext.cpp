#include "engine_pch.h"
#include "include/platform/OpenGL/GLFW_graphicsContext.h"
#include "systems/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	GLFW_GraphicsContext::GLFW_GraphicsContext(GLFWwindow* window) : m_window(window)
	{
	}

	void GLFW_GraphicsContext::init()
	{
		glfwMakeContextCurrent(m_window);
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (!result)
		{
			LOG_CORE_CRITICAL("FAILED TO INITIALISE GLAD!");
		}
		else
		{
			LOG_CORE_INFO("GLAD INITALIZED");
		}
	}

	void GLFW_GraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}