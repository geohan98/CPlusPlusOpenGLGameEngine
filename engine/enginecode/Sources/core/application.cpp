/** \file application.cpp
*/

#include "engine_pch.h"
#include "../enginecode/Headers/core/application.h"
#ifdef NG_PLATFORM_WINDOWS
#include "../enginecode/Headers/windows/GLFW_windowSys.h"
#include "../enginecode/Headers/windows/GLFW_inputPoller.h"
#endif // NG_PLATFORM_WINDOWS

#include "../enginecode/Headers/systems/profiler.h"

namespace Engine {

	Application* Application::s_instance = nullptr;

	glm::ivec2 Application::s_screenResolution;

	std::shared_ptr<Systems::ResourceManager> Application::m_resourceManager;

	float Application::s_deltaTime;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_log = std::shared_ptr<Systems::Log>(new Systems::Log());
		m_log->start();

		m_resourceManager = std::shared_ptr<Systems::ResourceManager>(new Systems::ResourceManager());
		m_resourceManager->start();

		m_time = std::shared_ptr<Systems::Time>(new Systems::Time());
		m_time->start();



#ifdef NG_PLATFORM_WINDOWS
		m_windowSystem = std::shared_ptr<Systems::WindowSystem>(new Systems::GLFW_WindowSys());
#endif // NG_PLATFORM_WINDOWS
		m_windowSystem->start();

		m_window = std::shared_ptr<Window>(Window::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		s_screenResolution = glm::ivec2(m_window->getWidth(), m_window->getHeight());

		m_layerStack = std::shared_ptr<Systems::LayerStack>(new Systems::LayerStack());
		m_layerStack->start();
	}

	Application::~Application()
	{
		m_layerStack->stop();
		m_window->close();
		m_windowSystem->stop();
		m_time->stop();
		m_resourceManager->stop();
		m_log->stop();
	}

	void Application::run()
	{
		//Engine Loop
		while (m_running)
		{
			//Timer Tick
			m_time->tick();
			//Update Delta Time
			s_deltaTime = m_time->getDeltaTime();
			//LOG_CORE_INFO("APPLICATION: FPS '{0}' , DeltaTime '{1}'", 1 / m_time->getDeltaTime(), m_time->getDeltaTime());
#ifdef NG_DEBUG
#endif // NG_DEBUG

			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); ++it)
			{
				(*it)->onUpdate(s_deltaTime);
			}

			m_window->onUpdate(s_deltaTime);
		}
	}

	void Application::onEvent(Events::Event& e)
	{
		//Dispatch Event to Application
		Events::EventDispatcher dispatcher(e);
		//Window Events
		dispatcher.dispatch<Events::WindowResize>(std::bind(&Application::onWindowResize, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowClose>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowMoved>(std::bind(&Application::onWindowMoved, this, std::placeholders::_1));
		dispatcher.dispatch<Events::WindowLostFocus>(std::bind(&Application::onWindowLostFocus, this, std::placeholders::_1));
		//Key Events
		dispatcher.dispatch<Events::KeyPressed>(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<Events::KeyReleased>(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<Events::KeyTyped>(std::bind(&Application::onKeyTyped, this, std::placeholders::_1));
		//Mouse Events
		dispatcher.dispatch<Events::MouseMoved>(std::bind(&Application::onMouseMove, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseScrolled>(std::bind(&Application::onMouseScrolled, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseButtonPressed>(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<Events::MouseButtonReleased>(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));

		//Send Event to Layer Stack
		for (auto it = m_layerStack->end(); it != m_layerStack->begin();)
		{
			(*--it)->onEvent(e);
		}
	}

	bool Application::onWindowResize(Events::WindowResize& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());
#endif // NG_DEBUG

		s_screenResolution = glm::ivec2(e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onWindowClose(Events::WindowClose& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: CLOSING APPLICATION");
#endif // NG_DEBUG

		m_running = false;
		return true;
	}

	bool Application::onWindowMoved(Events::WindowMoved& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG

		return true;
	}

	bool Application::onWindowLostFocus(Events::WindowLostFocus& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG

		return true;
	}

	bool Application::onKeyPressed(Events::KeyPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: KEY PRESSED '{0}'", e.getButton());
#endif // NG_DEBUG


		if (e.getButton() == KEY_ESCAPE)
		{
			m_running = false;
		}

		return true;
	}

	bool Application::onKeyReleased(Events::KeyReleased& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: KEY RELEASED '{0}'", e.getButton());
#endif // NG_DEBUG


		if (e.getButton() == KEY_ESCAPE)
		{
			m_running = false;
		}

		return true;
	}

	bool Application::onKeyTyped(Events::KeyTyped& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: KEY TYPED '{0}'", e.getButton());
#endif // NG_DEBUG

		return true;
	}

	bool Application::onMouseMove(Events::MouseMoved& e)
	{
#ifdef NG_DEBU
		LOG_CORE_INFO("APPLICATION: MOUSE MOVED '{0} , {1}'", e.getxPos(), e.getyPos());
#endif // NG_DEBUG

		return true;
	}

	bool Application::onMouseScrolled(Events::MouseScrolled& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: MOUSE SCROLLED '{0} , {1}'", e.getxDelta(), e.getyDelta());
#endif // NG_DEBUG

		return true;
	}

	bool Application::onMouseButtonPressed(Events::MouseButtonPressed& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: MOUSE BUTTON PRESSED '{0}'", e.getButton());
#endif // NG_DEBUG

		return true;
	}

	bool Application::onMouseButtonReleased(Events::MouseButtonReleased& e)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("APPLICATION: MOUSE BUTTON RELEASED '{0}'", e.getButton());
#endif // NG_DEBUG

		return true;
	}

}