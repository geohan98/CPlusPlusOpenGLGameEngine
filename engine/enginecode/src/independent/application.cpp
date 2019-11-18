/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#include "include/platform/OpenGL/GLFW_windowSys.h"
#include "include/platform/OpenGL/GLFW_windowImp.h"

namespace Engine {

	bool running = true;

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_logger = std::unique_ptr<Log>(new Log());
		m_logger->start();

		m_timer = std::unique_ptr<Time>(new Time());
		m_timer->start();

		m_windowSys = std::unique_ptr<WindowSystem>(new GLFW_WindowSys());
		m_windowSys->start();

		m_window.reset(GLFW_WindowImp::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	bool Application::onWindowResize(WindowResize& e)
	{
		LOG_CORE_INFO("WINDOW RESIZE: {0} x {1}", e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onWindowClose(WindowClose& e)
	{
		LOG_CORE_INFO("CLOSING APPLICATION");
		running = false;
		return true;
	}

	bool Application::onWindowMoved(WindowMoved& e)
	{
		LOG_CORE_INFO("WINDOW MOVED TO: {0} x {1}", e.getxPos(), e.getyPos());
		return true;
	}

	bool Application::onWindowLostFocus(WindowLostFocus& e)
	{
		LOG_CORE_INFO("WINDOW LOST FOCUS");
		return true;
	}

	bool Application::onKeyPressed(KeyPressed& e)
	{
		if (e.getRepeatCount() == 0)
		{
			LOG_CORE_INFO("KEY PRESSED: {0}", e.getButton());
		}
		else
		{
			LOG_CORE_INFO("KEY HELD: {0}", e.getButton());
		}

		return true;
	}

	bool Application::onKeyReleased(KeyReleased& e)
	{
		LOG_CORE_INFO("KEY RELEASED: {0}", e.getButton());
		return true;
	}

	bool Application::onKeyTyped(KeyTyped& e)
	{
		LOG_CORE_INFO("KEY TYPED: {0}", e.getButton());
		return true;
	}

	bool Application::onMouseMove(MouseMoved& e)
	{
		LOG_CORE_INFO("MOUSE MOVED TO: {0} x {1}", e.getxPos(), e.getyPos());
		return true;
	}

	bool Application::onMouseScrolled(MouseScrolled& e)
	{
		LOG_CORE_INFO("MOUSE SCROLLED: {0} x {1}", e.getxDelta(), e.getyDelta());
		return true;
	}

	bool Application::onMouseButtonPressed(MouseButtonPressed& e)
	{
		LOG_CORE_INFO("MOUSE BUTTON PRESSED: {0}", e.getButton());
		return true;
	}

	bool Application::onMouseButtonReleased(MouseButtonReleased& e)
	{
		LOG_CORE_INFO("MOUSE BUTTON RELEASED: {0}", e.getButton());
		return true;
	}

	Application::~Application()
	{
		m_window->close();
		m_windowSys->stop();
		m_timer->stop();
		m_logger->stop();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispactcher(e);
		//Application Events
		dispactcher.dispatch<WindowResize>(std::bind(&Application::onWindowResize, this, std::placeholders::_1));
		dispactcher.dispatch<WindowClose>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
		dispactcher.dispatch<WindowMoved>(std::bind(&Application::onWindowMoved, this, std::placeholders::_1));
		dispactcher.dispatch<WindowLostFocus>(std::bind(&Application::onWindowLostFocus, this, std::placeholders::_1));
		//Key Events
		dispactcher.dispatch<KeyPressed>(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		dispactcher.dispatch<KeyReleased>(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		dispactcher.dispatch<KeyTyped>(std::bind(&Application::onKeyTyped, this, std::placeholders::_1));
		//Mouse Events
		dispactcher.dispatch<MouseMoved>(std::bind(&Application::onMouseMove, this, std::placeholders::_1));
		dispactcher.dispatch<MouseScrolled>(std::bind(&Application::onMouseScrolled, this, std::placeholders::_1));
		dispactcher.dispatch<MouseButtonPressed>(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		dispactcher.dispatch<MouseButtonReleased>(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));
	}

	void Application::run()
	{
		while (running)
		{
			m_window->onUpdate(1 / 60);
		}
	}
}
