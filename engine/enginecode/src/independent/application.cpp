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

		m_logger.reset(I_Logger::getInstance());
		m_logger->start();

		m_timer.reset(I_Timer::getInstance());
		m_timer->start();
	}

	Application::~Application()
	{
		m_logger->stop();
		m_timer->stop();
	}

	void Application::run()
	{
		while (true)
		{
			m_timer->Tick();
			m_timer->Reset();
			m_logger->Info(1 / m_timer->getDeltaTime());
		}
	}

}
