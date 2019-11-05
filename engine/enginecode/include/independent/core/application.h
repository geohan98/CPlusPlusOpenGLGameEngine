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


namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
		std::shared_ptr<Log> m_logger;
		std::shared_ptr<Time> m_timer;
		std::shared_ptr<WindowSystem> m_window;
		static float m_timestep;

	private:
		static Application* s_instance; //!< Singleton instance of the application

		bool onClose(WindowClose& e);
		bool onResize(WindowResize& e);

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline static float getTimestep() { return m_timestep; }
		void onEvent(Event& e);
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}