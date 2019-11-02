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

	}

}
