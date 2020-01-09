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

	glm::ivec2 Application::s_screenResolution;

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

		m_window = std::shared_ptr<Window>(Window::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		s_screenResolution = glm::ivec2(m_window->getWidth(), m_window->getHeight());

		m_layerStack = std::shared_ptr<LayerStack>(new LayerStack());
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
			LOG_CORE_INFO("APPLICATION: FPS '{0}' , DeltaTime '{1}'", 1 / m_time->getDeltaTime(), m_time->getDeltaTime());
			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); ++it)
			{
				(*it)->onUpdate(s_deltaTime);
			}

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

		//Send Event to Layer Stack
		for (auto it = m_layerStack->end(); it != m_layerStack->begin();)
		{
			(*--it)->onEvent(e);
		}
	}

	bool Application::onWindowResize(WindowResize& e)
	{

		LOG_CORE_INFO("APPLICATION: WINDOW RESIZE '{0} x {1}'", e.getWidth(), e.getHeight());

		s_screenResolution = glm::ivec2(e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onWindowClose(WindowClose& e)
	{

		LOG_CORE_INFO("APPLICATION: CLOSING APPLICATION");

		m_running = false;
		return true;
	}

	bool Application::onWindowMoved(WindowMoved& e)
	{

		LOG_CORE_INFO("APPLICATION: WINDOW MOVED '{0} , {1}'", e.getxPos(), e.getyPos());

		return true;
	}

	bool Application::onWindowLostFocus(WindowLostFocus& e)
	{

		LOG_CORE_INFO("APPLICATION: WINDOW LOST FOCUS '{0} , {1}'", e.getxPos(), e.getyPos());

		return true;
	}

	bool Application::onKeyPressed(KeyPressed& e)
	{

		LOG_CORE_INFO("APPLICATION: KEY PRESSED '{0}'", e.getButton());


		if (e.getButton() == KEY_ESCAPE)
		{
			m_running = false;
		}

		return true;
	}

	bool Application::onKeyReleased(KeyReleased& e)
	{

		LOG_CORE_INFO("APPLICATION: KEY RELEASED '{0}'", e.getButton());


		if (e.getButton() == KEY_ESCAPE)
		{
			m_running = false;
		}

		return true;
	}

	bool Application::onKeyTyped(KeyTyped& e)
	{

		LOG_CORE_INFO("APPLICATION: KEY TYPED '{0}'", e.getButton());

		return true;
	}

	bool Application::onMouseMove(MouseMoved& e)
	{

		LOG_CORE_INFO("APPLICATION: MOUSE MOVED '{0} , {1}'", e.getxPos(), e.getyPos());

		return true;
	}

	bool Application::onMouseScrolled(MouseScrolled& e)
	{

		LOG_CORE_INFO("APPLICATION: MOUSE SCROLLED '{0} , {1}'", e.getxDelta(), e.getyDelta());

		return true;
	}

	bool Application::onMouseButtonPressed(MouseButtonPressed& e)
	{

		LOG_CORE_INFO("APPLICATION: MOUSE BUTTON PRESSED '{0}'", e.getButton());

		return true;
	}

	bool Application::onMouseButtonReleased(MouseButtonReleased& e)
	{

		LOG_CORE_INFO("APPLICATION: MOUSE BUTTON RELEASED '{0}'", e.getButton());

		return true;
	}

}