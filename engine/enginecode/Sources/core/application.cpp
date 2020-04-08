/** \file application.cpp
*/

#include "engine_pch.h"
#include "Headers/core/application.h"
#include "Headers/systems/log.h"
#include "Headers/iniParser.h"
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

	Application::Application(char* _name)
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

		IniParser config = IniParser("config.ini");

		Engine::WindowProperties win = Engine::WindowProperties();
		win.m_title = _name;

		win.m_width = config.getDataInt("width");
		win.m_height = config.getDataInt("height");
		win.m_isFullScreen = config.getDataBool("fullscreen");

		m_window = std::shared_ptr<Window>(Window::create(win));
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		m_layerStack = std::shared_ptr<Systems::LayerStack>(new Systems::LayerStack());
		m_layerStack->start();

		m_physics = Systems::Physics::GetInstance();
		m_physics->start();

		m_audioSystem->start();
		m_audioSystem->loadSound("assets/audio/woo.mp3", false);
		// alternatively
		// START_SOUND_ENGINE();
		// LOAD_SOUND("assets/audio/woo.mp3", false);
	}

	Application::~Application()
	{
		m_physics->stop();
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

			//Update Physics
			m_physics->getWorld()->update(s_deltaTime);

			//Update Audio 
			m_audioSystem->update();

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

	void Application::close()
	{
		m_running = false;
	}

#pragma endregion

#pragma region Events

	bool Application::onWindowClose(Events::WindowClose& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: CLOSING APPLICATION");
#endif // NG_DEBUG

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