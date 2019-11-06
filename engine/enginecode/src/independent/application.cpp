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

		m_logger = std::unique_ptr<Log>(new Log());
		m_logger->start();

		m_timer = std::unique_ptr<Time>(new Time());
		m_timer->start();

		m_window = std::unique_ptr<WindowSystem>(new GLFW_WindowSys);
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
		LOG_CORE_INFO("WINDOW RESIZE: {0} x {1}", e.getWidth(), e.getHeight());
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
