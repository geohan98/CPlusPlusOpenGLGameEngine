#include "engine_pch.h"
#include "Headers/windows/GLFW_windowImp.h"
#include "Headers/windows/GLFW_graphicsContext.h"
#include "Headers/systems/log.h"

#include <GLFW/glfw3.h>

namespace Engine
{
	void GLFW_WindowImp::init(const WindowProperties& properties)
	{
		m_properties = properties;

		if (m_properties.m_isFullScreen)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			m_nativeWindow = glfwCreateWindow(mode->width, mode->height, m_properties.m_title.c_str(), glfwGetPrimaryMonitor(), NULL);
			if (!m_nativeWindow)
			{
#ifdef NG_DEBUG
				LOG_CORE_CRITICAL("[WINDOW][GLFW][FAILED TO CREATE GLFW WINDOW]");
#endif // NG_DEBUG
				return;
			}
			else
			{
#ifdef NG_DEBUG
				LOG_CORE_WARN("[WINDOW][GLFW][GLFW WINDOW CREATED]");
#endif // NG_DEBUG
			}
		}
		else
		{
			m_nativeWindow = glfwCreateWindow(m_properties.m_width, m_properties.m_height, m_properties.m_title.c_str(), NULL, NULL);
			if (!m_nativeWindow)
			{
#ifdef NG_DEBUG
				LOG_CORE_CRITICAL("[WINDOW][GLFW][FAILED TO CREATE GLFW WINDOW]");
#endif // NG_DEBUG
				return;
			}
			else
			{
#ifdef NG_DEBUG
				LOG_CORE_WARN("[WINDOW][GLFW][GLFW WINDOW CREATED]");
#endif // NG_DEBUG
			}
		}

		m_context = std::unique_ptr<GraphicsContext>(new GLFW_GraphicsContext(m_nativeWindow));
		m_context->init();

		glfwSetWindowUserPointer(m_nativeWindow, &m_callBack);

		//Application Event Callbacks
		glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* window)
			{
				LOG_CORE_TRACE("[WINDOW][GLFW][WINDOW CLOSE]");
				std::function<void(Events::Event&)>& callback = *(std::function<void(Events::Event&)>*)glfwGetWindowUserPointer(window);
				Events::WindowClose event;
				callback(event);
			}
		);

		glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height)
			{
				LOG_CORE_TRACE("[WINDOW][GLFW][WINDOW SET SIZE: {0} x {1}]", width, height);
				std::function<void(Events::Event&)>& callback = *(std::function<void(Events::Event&)>*)glfwGetWindowUserPointer(window);
				Events::WindowResize event(width, height);
				callback(event);
			}
		);

		glfwSetFramebufferSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height)
			{
				LOG_CORE_TRACE("[WINDOW][GLFW][FRAME BUFFER SET SIZE: {0} x {1}]", width, height);
				glViewport(0, 0, width, height);
			}
		);

		//Keyboard Event Callbacks
		glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				std::function<void(Events::Event&)>& callback = *(std::function<void(Events::Event&)>*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					Events::KeyPressed event(key, 0);
					callback(event);
				}
				break;
				case  GLFW_REPEAT:
				{
					Events::KeyPressed event(key, 1);
					callback(event);
				}
				break;
				case GLFW_RELEASE:
				{
					Events::KeyReleased event(key);
					callback(event);
				}
				break;
				}
			}
		);

		glfwSetCharCallback(m_nativeWindow, [](GLFWwindow* window, unsigned int unicodeCodepoint)
			{
				std::function<void(Events::Event&)>& callback = *(std::function<void(Events::Event&)>*)glfwGetWindowUserPointer(window);
				Events::KeyTyped event(unicodeCodepoint);
				callback(event);
			}
		);

		//Mouse Event Callbacks
		glfwSetCursorPosCallback(m_nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				std::function<void(Events::Event&)>& callback = *(std::function<void(Events::Event&)>*)glfwGetWindowUserPointer(window);
				Events::MouseMoved event(xPos, yPos);
				callback(event);
			}
		);

		glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				std::function<void(Events::Event&)>& callback = *(std::function<void(Events::Event&)>*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					Events::MouseButtonPressed event(button);
					callback(event);
				}
				break;
				case GLFW_RELEASE:
				{
					Events::MouseButtonReleased event(button);
					callback(event);
				}
				break;
				}
			}
		);

		glfwSetScrollCallback(m_nativeWindow, [](GLFWwindow* window, double xDelta, double yDelta)
			{
				std::function<void(Events::Event&)>& callback = *(std::function<void(Events::Event&)>*)glfwGetWindowUserPointer(window);
				Events::MouseScrolled event(xDelta, yDelta);
				callback(event);
			}
		);

	}

	void GLFW_WindowImp::close()
	{
		m_context.release();
#ifdef NG_DEBUG
		LOG_CORE_WARN("[WINDOW][GLFW][DESTROYING GLFW WINDOW]");
#endif // NG_DEBUG
		glfwDestroyWindow(m_nativeWindow);
	}

	GLFW_WindowImp::GLFW_WindowImp(const WindowProperties& properties)
	{
		LOG_CORE_WARN("[WINDOW][GLFW][CREATING GLFW WINDOW]");
		init(properties);
	}

	GLFW_WindowImp::~GLFW_WindowImp()
	{
	}

	void GLFW_WindowImp::onUpdate(float deltaTime)
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}

	void GLFW_WindowImp::onResize(unsigned int width, unsigned int height)
	{
		LOG_CORE_INFO("[WINDOW][GLFW][RESIZE WINDOW]");
		glfwSetWindowSize(m_nativeWindow, width, height);
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

	void GLFW_WindowImp::setEventCallback(const std::function<void(Events::Event&)>& callback)
	{
		m_callBack = callback;
	}

	inline void GLFW_WindowImp::setFullScreenMode(bool _fullscreen)
	{
		if (_fullscreen == m_properties.m_isFullScreen)
		{
			LOG_CORE_INFO("ALREADY IN THAT MODE");
			return;
		}
		if (_fullscreen)
		{
			glfwGetWindowSize(m_nativeWindow, &m_properties.m_width, &m_properties.m_height);

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			glfwSetWindowMonitor(m_nativeWindow, nullptr, 0, 0, mode->width, mode->height, 0);
		}
		else
		{
			glfwSetWindowMonitor(m_nativeWindow, nullptr, 10, 10, m_properties.m_width, m_properties.m_height, 0);
		}
		m_properties.m_isFullScreen = _fullscreen;
	}

	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFW_WindowImp(properties);
	}
}