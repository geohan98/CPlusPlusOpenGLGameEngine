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

		logger = std::shared_ptr<Log>(new Log());
		logger->start();
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
	}

}
