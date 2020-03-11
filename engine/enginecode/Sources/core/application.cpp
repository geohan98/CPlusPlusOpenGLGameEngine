/** \file application.cpp
*/

#include "engine_pch.h"
#include "Headers/core/application.h"
#include "Headers/systems/log.h"
#include "Headers/systems/profiler.h"
#ifdef NG_PLATFORM_WINDOWS
#include "Headers/windows/GLFW_windowSys.h"
#include "Headers/windows/GLFW_inputPoller.h"
#endif // NG_PLATFORM_WINDOWS

namespace Engine {

#pragma region Statics

	Application* Application::s_instance = nullptr;
	std::shared_ptr<Systems::ResourceManager> Application::m_resourceManager;
	float Application::s_deltaTime;

#pragma endregion

#pragma region Constructor & Destructor

	Application::Application(char* _name, int _width, int _height)
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_log = std::shared_ptr<Systems::Log>(new Systems::Log());
		m_log->start();

		m_time = std::shared_ptr<Systems::Time>(new Systems::Time());
		m_time->start();

		m_resourceManager = std::shared_ptr<Systems::ResourceManager>(new Systems::ResourceManager());
		m_resourceManager->start();

#ifdef NG_PLATFORM_WINDOWS
		m_windowSystem = std::shared_ptr<Systems::WindowSystem>(new Systems::GLFW_WindowSys());
#endif // NG_PLATFORM_WINDOWS
		m_windowSystem->start();

		Engine::WindowProperties win = Engine::WindowProperties();
		win.m_title = _name;
		win.m_width = _width;
		win.m_height = _height;

		m_window = std::shared_ptr<Window>(Window::create(win));
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		m_layerStack = std::shared_ptr<Systems::LayerStack>(new Systems::LayerStack());
		m_layerStack->start();
	}

	Application::~Application()
	{
		PROFILE_SCOPE("APP DESTRUCTOR");
		m_layerStack->stop();
		m_window->close();
		m_windowSystem->stop();
		m_resourceManager->stop();
		m_time->stop();
		m_log->stop();
	}
#pragma endregion

#pragma region Run & Event

	void Application::run()
	{
		while (m_running) //Run Loop
		{
			//Timer Tick
			m_time->tick();
			//Update Delta Time
			s_deltaTime = m_time->getDeltaTime();
			//Update Layer Stack
			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); ++it)
			{
				(*it)->onUpdate(s_deltaTime);
			}
			//Update Window
			m_window->onUpdate(s_deltaTime);
		}
	}

	void Application::onEvent(Events::Event& e)
	{
		//Dispatch Event to Application
		Events::EventDispatcher dispatcher(e);

		dispatcher.dispatch<Events::WindowClose>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<Events::KeyPressed>(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));

		//Send Event to Layer Stack
		for (auto it = m_layerStack->end(); it != m_layerStack->begin();)
		{
			(*--it)->onEvent(e);
		}
	}

#pragma endregion

#pragma region Events

	bool Application::onWindowClose(Events::WindowClose& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: CLOSING APPLICATION");
#endif // NG_DEBUG
#pragma endregion

		m_running = false;

		return true;
	}

	bool Application::onKeyPressed(Events::KeyPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("[APPLICATION][EVENT][KEY PRESS '{0}']", e.getButton());
#endif // NG_DEBUG

#ifdef NG_DEBUG
		if (e.getButton() == KEY_ESCAPE)
		{
			m_running = false;
		}
#endif // NG_DEBUG

		return true;
	}

#pragma endregion


}