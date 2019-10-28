#include "include/platform/GLFW/GLFW_GraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFW_GraphicsContext::GLFW_GraphicsContext(GLFWwindow * window) : m_window(window)
{

}

void GLFW_GraphicsContext::init()
{
	glfwMakeContextCurrent(m_window);
	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void GLFW_GraphicsContext::swapBuffers()
{
	glfwSwapBuffers(m_window);
}
