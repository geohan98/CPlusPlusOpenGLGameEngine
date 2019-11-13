/** \file application.h
*/
#pragma once
#include "systems/log.h"
#include "systems/time.h"
#include "systems/events/event.h"
#include "systems/events/applicationEvents.h"
#include "systems/events/keyEvents.h"
#include "systems/events/mouseEvents.h"
#include "windows/windowSystem.h"
#include "windows/window.h"


namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application();															//!< Constructor
		std::unique_ptr<Log> m_logger;
		std::unique_ptr<Time> m_timer;
		std::shared_ptr<Window> m_window;
		std::unique_ptr<WindowSystem> m_windowSys;
		static float m_timestep;
	private:
		static Application* s_instance;											//!< Singleton instance of the application
		//Application Events
		bool onWindowResize(WindowResize& e);
		bool onWindowClose(WindowClose& e);
		bool onWindowMoved(WindowMoved& e);
		bool onWindowLostFocus(WindowLostFocus& e);
		//Key Events
		bool onKeyPressed(KeyPressed& e);
		bool onKeyReleased(KeyReleased& e);
		bool onKeyTyped(KeyTyped& e);
		//Mouse Events
		bool onMouseMove(MouseMoved& e);
		bool onMouseScrolled(MouseScrolled& e);
		bool onMouseButtonPressed(MouseButtonPressed& e);
		bool onMouseButtonReleased(MouseButtonReleased& e);
	public:
		virtual ~Application();													//!< Deconstructor
		inline static Application& getInstance() { return *s_instance; }		//!< Instance getter from singleton pattern
		std::shared_ptr<Window> getWindow() { return m_window; }
		inline static float getTimestep() { return m_timestep; }
		void onEvent(Event& e);
		void run();																//!< Main loop
	};

	// To be defined in users code
	Application* startApplication();											//!< Function definition which provides an entry hook

}