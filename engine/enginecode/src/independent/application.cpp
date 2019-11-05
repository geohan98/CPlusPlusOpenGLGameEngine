/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#include "include/platform/OpenGL/GLFW_windowSys.h"
#include "include/platform/OpenGL/GLFW_windowImp.h"

namespace Engine {

	bool running = true;

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_logger = std::shared_ptr<Log>(new Log());
		m_logger->start();

		m_timer = std::shared_ptr<Time>(new Time());
		m_timer->start();

		m_window = std::shared_ptr<WindowSystem>(new GLFW_WindowSys);
		m_window->start();
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	bool Application::onClose(WindowClose& e)
	{
		LOG_CORE_INFO("CLOSING APPLICATION");
		running = false;
		return true;
	}

	bool Application::onResize(WindowResize& e)
	{
		LOG_CORE_INFO("Window Resize: {0} x {1}", e.getWidth(), e.getHeight());
		return true;
	}

	Application::~Application()
	{
		m_window->stop();
		m_timer->stop();
		m_logger->stop();
		std::cin.get();
	}

	void Application::onEvent(Event& e)
	{
		//LOG_CORE_INFO(e);
		EventDispatcher dispactcher(e);
		dispactcher.dispatch<WindowClose>(std::bind(&Application::onClose, this, std::placeholders::_1));
		dispactcher.dispatch<WindowResize>(std::bind(&Application::onResize, this, std::placeholders::_1));
	}

	void Application::run()
	{
		while (running)
		{
			m_window->update(1 / 60);
		}
	}
}



/*
	void errorCallback(int errorCode, const char* errorDescription)
	{
		LOG_CORE_ERROR("Error Code: %i - %s", errorCode, errorDescription);
	}


	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			running = false;
		}
	}

	void textCallback(GLFWwindow* window, unsigned int unicodeCodepoint)
	{
		LOG_CORE_INFO((char)unicodeCodepoint);
	}

	void mouseMoveCallback(GLFWwindow* window, double x, double y)
	{
		LOG_CORE_INFO("Mouse Moved: {0} {1}", x, y);
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) LOG_CORE_INFO("Right Mouse Button Pressed");
		if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) LOG_CORE_INFO("Middle Mouse Button Pressed");
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) LOG_CORE_INFO("Left Mouse Button Pressed");
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) LOG_CORE_INFO("Right Mouse Button Released");
		if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) LOG_CORE_INFO("Middle Mouse Button Released");
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) LOG_CORE_INFO("Left Mouse Button Released");
	}

	void windowResizeCallback(GLFWwindow* window, int width, int height)
	{
		LOG_CORE_INFO("Window Resize: {0} x {1}", width, height);
	}

	void windowCloseCallback(GLFWwindow* window)
	{
		running = false;
	}
	*/
