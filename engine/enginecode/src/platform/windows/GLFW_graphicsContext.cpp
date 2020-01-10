#include "engine_pch.h"
#include "include/platform/windows/GLFW_graphicsContext.h"
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
#ifdef NG_DEBUG
			LOG_CORE_CRITICAL("FAILED TO INITIALISE GLAD");
#endif // NG_DEBUG
		}
		else
		{
#ifdef NG_DEBUG
			LOG_CORE_WARN("GLAD INITALIZED");
#endif // NG_DEBUG

			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback([](GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam) {
#ifdef NG_DEBUG
					LOG_CORE_INFO("OpenGL DEBUG: [Type {0}] [ID {1}] [Severity {2}]; {3}", type, id, severity, message);
#endif // NG_DEBUG
		}, 0);
	}
}

	void GLFW_GraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}