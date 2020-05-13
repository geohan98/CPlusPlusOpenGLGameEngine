#pragma once
#include "Headers/systems/log.h"
#include "Headers/systems/time.h"
#include "Headers/windows/windowSystem.h"
#include "Headers/windows/window.h"
#include "Headers/systems/resourceManager.h"
#include "Headers/systems/layerStack.h"
#include "Headers/systems/Physics.h"
#include "Headers/audio/audio.h"


namespace Engine {

	/**
	 *  Application, Handles Events system init and update loop
	 */
	class Application
	{
	protected:
		Application(char* _name); ///< Constructor
		std::shared_ptr<Systems::Log> m_log; ///< Logger System
		std::shared_ptr<Systems::Time> m_time; ///< Timer System
		std::shared_ptr<Systems::WindowSystem> m_windowSystem; ///< Window System
		std::shared_ptr<Window> m_window; ///< Window
		static std::shared_ptr<Systems::ResourceManager> m_resourceManager; ///< Resource Manager System
		std::shared_ptr<Systems::LayerStack> m_layerStack; ///< Layer Stack
		std::shared_ptr<Systems::Audio> m_audioSystem;
		std::shared_ptr<Systems::Physics> m_physics; ///< Physics System

		glm::ivec2 m_windowSize;
		bool fullscreen;
	private:
		static Application* s_instance; ///< Pointer to this application
		bool m_running = true; ///< Should the update loop run
		static float s_deltaTime; ///< Time Since Last Frame
		bool onWindowClose(Events::WindowClose& e);
		bool onKeyPressed(Events::KeyPressed& e);
		bool onWindowMove(Events::WindowMoved& e);
		bool onWindowResize(Events::WindowResize& e);
	public:
		virtual ~Application(); ///< Deconstructor
		void run(); ///< Update Loop
		void onEvent(Events::Event& e); ///< Called On an Event
		inline static Application& getInstance() { return *s_instance; } ///< Return an Application Pointer
		void close();
		void toggleFullscreen();
		inline std::shared_ptr<Window> getWindow() { return m_window; } ///< Returns The Window
		inline bool isFullscreen() { return fullscreen; }
		inline glm::ivec2 getWindowSize() { return m_windowSize; }
		inline std::shared_ptr<Systems::ResourceManager> getResourceManager() { return m_resourceManager; }
	};

	Application* startApplication();
}