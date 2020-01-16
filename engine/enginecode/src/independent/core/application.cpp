/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"
#ifdef NG_PLATFORM_WINDOWS
#include "include/platform/windows/GLFW_windowSys.h"
#include "include/platform/windows/GLFW_inputPoller.h"
#endif // NG_PLATFORM_WINDOWS

namespace Engine {

	Application* Application::s_instance = nullptr;

	std::shared_ptr<ResourceManager> Application::m_resourceManager;

	float Application::s_deltaTime;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_log = std::shared_ptr<Log>(new Log());
		m_log->start();

		m_resourceManager = std::shared_ptr<ResourceManager>(new ResourceManager());
		m_resourceManager->start();

		m_time = std::shared_ptr<Time>(new Time());
		m_time->start();



#ifdef NG_PLATFORM_WINDOWS
		m_windowSystem = std::shared_ptr<WindowSystem>(new GLFW_WindowSys());
#endif // NG_PLATFORM_WINDOWS
		m_windowSystem->start();
		WindowProperties prop = WindowProperties("Engine App", 1280, 720, false);
		m_window = std::shared_ptr<Window>(Window::create(prop));
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
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
#ifdef NG_DEBUG
			LOG_CORE_INFO("APPLICATION: FPS '{0}' , DeltaTime '{1}'", 1 / m_time->getDeltaTime(), m_time->getDeltaTime());
#endif // NG_DEBUG

			m_window->onUpdate(s_deltaTime);
		}
	}

	void Application::onEvent(Event& e)
	{
		//Dispatch Event to Application
		EventDispatcher dispatcher(e);
		//Window Events
		dispatcher.dispatch<WindowResize>(std::bind(&Application::onWindowResize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowClose>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowMoved>(std::bind(&Application::onWindowMoved, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocus>(std::bind(&Application::onWindowLostFocus, this, std::placeholders::_1));
		//Key Events
		dispatcher.dispatch<KeyPressed>(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		dispatcher.dispatch<KeyReleased>(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		dispatcher.dispatch<KeyTyped>(std::bind(&Application::onKeyTyped, this, std::placeholders::_1));
		//Mouse Events
		dispatcher.dispatch<MouseMoved>(std::bind(&Application::onMouseMove, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolled>(std::bind(&Application::onMouseScrolled, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleased>(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));
	}

	bool Application::onWindowResize(WindowResize& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());

#endif // NG_DEBUG

		return true;
	}

	bool Application::onWindowClose(WindowClose& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: CLOSING APPLICATION");

#endif // NG_DEBUG

		m_running = false;

		return true;
	}

	bool Application::onWindowMoved(WindowMoved& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());

#endif // NG_DEBUG

		return true;
	}

	bool Application::onWindowLostFocus(WindowLostFocus& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());

#endif // NG_DEBUG

		return true;
	}

	bool Application::onKeyPressed(KeyPressed& e)
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

	bool Application::onKeyReleased(KeyReleased& e)
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

	bool Application::onKeyTyped(KeyTyped& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: KEY TYPED '{0}'", e.getButton());

#endif // NG_DEBUG

		return true;
	}

	bool Application::onMouseMove(MouseMoved& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: MOUSE MOVED '{0} , {1}'", e.getxPos(), e.getyPos());

#endif // NG_DEBUG

		return true;
	}

	bool Application::onMouseScrolled(MouseScrolled& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: MOUSE SCROLLED '{0} , {1}'", e.getxDelta(), e.getyDelta());

#endif // NG_DEBUG

		return true;
	}

	bool Application::onMouseButtonPressed(MouseButtonPressed& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: MOUSE BUTTON PRESSED '{0}'", e.getButton());

#endif // NG_DEBUG

		return true;
	}

	bool Application::onMouseButtonReleased(MouseButtonReleased& e)
	{
#ifdef NG_DEBUG

		LOG_CORE_INFO("APPLICATION: MOUSE BUTTON RELEASED '{0}'", e.getButton());

#endif // NG_DEBUG

		return true;
	}

}