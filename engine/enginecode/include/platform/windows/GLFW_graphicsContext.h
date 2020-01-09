#pragma once

#include "windows/graphicsContext.h"

#include "systems/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	/**
	 * GL Vertex Buffer
	 */
	class GLFW_GraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_window; ///< A GLFW window
	public:
		GLFW_GraphicsContext(GLFWwindow* window); ///< Constructor
		void init() override; ///< initialize the graphics context
		void swapBuffers() override; ///< swap buffer, display new frame to window
	};
}