#pragma once

#include "windows/graphicsContext.h"

#include "systems/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace Engine
{
	class GLFW_GraphicsContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_window;
	public:
		GLFW_GraphicsContext(GLFWwindow* window);
		void init() override;
		void swapBuffers() override;
	};
}