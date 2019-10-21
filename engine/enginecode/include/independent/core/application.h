/** \file application.h
*/
#pragma once
#include "systems/log.h"
#include "systems/timer.h"

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
		std::shared_ptr<I_Logger> m_logger;
		std::shared_ptr<I_Timer> m_timer;
	private:
		static Application* s_instance; //!< Singleton instance of the application
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}