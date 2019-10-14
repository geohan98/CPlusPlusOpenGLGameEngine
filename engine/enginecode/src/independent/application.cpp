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
		m_timer = std::shared_ptr<Timer>(new Timer());

	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		m_timer->start();
		m_logger->start();
		Log::getLogger()->info(m_timer->getAppStart());
	}

}
