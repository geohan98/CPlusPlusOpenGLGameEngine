/** \file application.cpp
*/


#include "engine_pch.h"
#include "core/application.h"

#include "systems/EventDispatcher.h"



namespace Engine {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_logger.reset(I_Logger::getInstance());
		m_logger->start();

		m_timer.reset(I_Timer::getInstance());
		m_timer->start();
	}

	bool Application::onClose(WindowResize& e)
	{
		m_logger->Info("Closing Application");
		return false;
	}

	bool Application::onResize(WindowResize& e)
	{
		m_logger->Info("Resizing Window");
		return false;
	}

	Application::~Application()
	{
		m_logger->stop();
		m_timer->stop();
	}

	void Application::onEvent(Event& e)
	{
	}

	void Application::run()
	{

	}

}
