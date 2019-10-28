#pragma once
#include "windows/graphicsContext.h"

class GLFWwindow;

class GLFW_GraphicsContext : public GraphicsContext
{
public:
	GLFW_GraphicsContext(GLFWwindow* window);
	void init() override;
	void swapBuffers() override;
private:
	GLFWwindow* m_window;
};