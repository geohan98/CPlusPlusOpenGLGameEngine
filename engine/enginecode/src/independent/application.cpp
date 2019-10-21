/** \file application.cpp
*/


#include "engine_pch.h"
#include "core/application.h"

#include "systems/log.h"
#include "systems/timer.h"


namespace Engine {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_logger.reset(new I_Logger());
		m_logger->start();

		m_timer.reset(new I_Timer());
		m_timer->start();
		I_Logger::getLogger()->info("Timer Started At: {0}", I_Timer::getAppStart());
	}

	Application::~Application()
	{
		m_logger->stop();
		m_timer->stop();
		std::cin.get();
	}

	void Application::run()
	{
		bool isRunning = true;
		float frameRate = 60.0f;

		while (isRunning)
		{
			m_timer->Tick();

				m_timer->Reset();
				I_Logger::getLogger()->info(1 / m_timer->getDeltaTime());
		}
	}

}
