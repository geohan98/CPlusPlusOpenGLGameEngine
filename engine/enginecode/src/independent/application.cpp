/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"



namespace Engine {
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
	}

	bool Application::onClose(WindowResize& e)
	{
		return false;
	}

	bool Application::onResize(WindowResize& e)
	{
		return false;
	}

	Application::~Application()
	{
		std::cin.get();
	}

	void Application::onEvent(Event& e) {}

	void Application::run()
	{
		while (true)
		{
			m_timer->reset();
			LOG_CORE_TRACE(1 / TIME_DELTA_TIME);
			m_timer->tick();
		}
	}

}
