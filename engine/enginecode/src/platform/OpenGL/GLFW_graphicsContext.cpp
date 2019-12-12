#include "engine_pch.h"
#include "include/platform/OpenGL/GLFW_graphicsContext.h"
#include "systems/log.h"

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

			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback([](GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam) {
				//LOG_CORE_INFO("OpenGL Debug: [Type {0}] [ID {1}] [Severity {2}]; {3}", type, id, severity, message);
			}, 0);
		}
	}

	void GLFW_GraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}