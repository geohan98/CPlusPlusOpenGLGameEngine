#pragma once
#include "systems/log.h"
#include "systems/time.h"
#include "windows/windowSystem.h"
#include "windows/window.h"
#include "systems/resourceManager.h"
#include "systems/layerStack.h"

namespace Engine {


	/**
	 *  Application, Handles Events system init and update loop
	 */
	class Application
	{
	protected:
		Application(); ///< Constructor
		std::shared_ptr<Log> m_log; ///< Logger System
		std::shared_ptr<Time> m_time; ///< Timer System
		std::shared_ptr<WindowSystem> m_windowSystem; ///< Window System
		std::shared_ptr<Window> m_window; ///< Window
		static std::shared_ptr<ResourceManager> m_resourceManager; ///< Resource Manager System
		std::shared_ptr<LayerStack> m_layerStack; ///< Layer Stack
	private:
		static Application* s_instance; ///< Pointer to this application
		bool m_running = true; ///< Should the update loop run
		static glm::ivec2 s_screenResolution; ///< Window Resolution
		static float s_deltaTime; ///< Time Since Last Frame
		//Window Events
		bool onWindowResize(WindowResize& e);				///< Window Resize Event
		bool onWindowClose(WindowClose& e);					///< Window Close Event
		bool onWindowMoved(WindowMoved& e);					///< Window Move Event
		bool onWindowLostFocus(WindowLostFocus& e);			///< Window Lost Focus Event
		//Key Events
		bool onKeyPressed(KeyPressed& e);					///< Key Press Event
		bool onKeyReleased(KeyReleased& e);					///< Key Release Event
		bool onKeyTyped(KeyTyped& e);						///< Key Type Event
		//Mouse Events
		bool onMouseMove(MouseMoved& e);					///< Mouse Move Event
		bool onMouseScrolled(MouseScrolled& e);				///< Mouse Scrolled Event
		bool onMouseButtonPressed(MouseButtonPressed& e);	///< Mouse Button Press Event
		bool onMouseButtonReleased(MouseButtonReleased& e);	///< Mouse Button Release Event
	public:
		virtual ~Application(); ///< Deconstructor
		inline static Application& getInstance() { return *s_instance; } ///< Return an Application Pointer
		inline static float getdeltaTime() { return s_deltaTime; } ///< Returns Time Since Last Frame
		inline std::shared_ptr<Window> getWindow() { return m_window; } ///< Returns The Window
		void run(); ///< Update Loop
		void onEvent(Event& e); ///< Called On an Event
	};

	Application* startApplication();

}