#include "engine_pch.h"
#include "include/platform/OpenGL/GLFW_windowImp.h"
#include "include/platform/OpenGL/GLFW_graphicsContext.h"
#include "systems/log.h"

#include <GLFW/glfw3.h>

namespace Engine
{
	void GLFW_WindowImp::init(const WindowProperties& properties)
	{
		m_properties = properties;

		if (!glfwInit())
		{
			LOG_CORE_CRITICAL("FAILED TO INITALIZE GLFW");
			return;
		}
		else
		{
			LOG_CORE_INFO("GLFW INITALIZED");
		}

		GLFWwindow* m_nativeWindow = glfwCreateWindow(m_properties.m_width, m_properties.m_height, m_properties.m_title.c_str(), NULL, NULL);
		if (!m_nativeWindow)
		{
			LOG_CORE_CRITICAL("FAILED TO CREATE GLFW WINDOW");
			return;
		}
		else
		{
			LOG_CORE_INFO("GLFW WINDOW CREATED");
		}

		m_context = std::unique_ptr<GraphicsContext>(new GLFW_GraphicsContext(m_nativeWindow));
		m_context->init();

		glfwSetWindowUserPointer(m_nativeWindow, &m_callBack);

		glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* window)
			{
				std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
				WindowClose event;
				callback(event);
			}
		);

		glfwSetCursorPosCallback(m_nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
				MouseMoved event(xPos, yPos);
				callback(event);
			});

		glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height)
			{
				std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
				WindowResize event(width, height);
				callback(event);
			});
	}
	void GLFW_WindowImp::close()
	{
		m_context.release();
		LOG_CORE_WARN("DESTROYING GLFW WINDOW");
		glfwDestroyWindow(m_nativeWindow);
		LOG_CORE_WARN("TERMINATING GLFW");
		glfwTerminate();
	}
	GLFW_WindowImp::GLFW_WindowImp(const WindowProperties& properties)
	{
		init(properties);
	}
	GLFW_WindowImp::~GLFW_WindowImp()
	{
		close();
	}
	void GLFW_WindowImp::onUpdate(float timestep)
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}
	void GLFW_WindowImp::onResize(unsigned int width, unsigned int height)
	{
	}
	void GLFW_WindowImp::setVSync(bool VSync)
	{
		if (VSync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_properties.m_isVSync = VSync;
	}
	void GLFW_WindowImp::setEventCallback(const std::function<void(Event&)>& callback)
	{
		m_callBack = callback;
	}

	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFW_WindowImp(properties);
	}
}