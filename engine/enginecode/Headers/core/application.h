#pragma once
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/systems/time.h"
#include "../enginecode/Headers/windows/windowSystem.h"
#include "../enginecode/Headers/windows/window.h"
#include "../enginecode/Headers/systems/resourceManager.h"
#include "../enginecode/Headers/systems/layerStack.h"

namespace Engine {


	/**
	 *  Application, Handles Events system init and update loop
	 */
	class Application
	{
	protected:
		Application(); ///< Constructor
		std::shared_ptr<Systems::Log> m_log; ///< Logger System
		std::shared_ptr<Systems::Time> m_time; ///< Timer System
		std::shared_ptr<Systems::WindowSystem> m_windowSystem; ///< Window System
		std::shared_ptr<Window> m_window; ///< Window
		static std::shared_ptr<Systems::ResourceManager> m_resourceManager; ///< Resource Manager System
		std::shared_ptr<Systems::LayerStack> m_layerStack; ///< Layer Stack
	private:
		static Application* s_instance; ///< Pointer to this application
		bool m_running = true; ///< Should the update loop run
		static glm::ivec2 s_screenResolution; ///< Window Resolution
		static float s_deltaTime; ///< Time Since Last Frame
		//Window Events
		bool onWindowResize(Events::WindowResize& e);				///< Window Resize Event
		bool onWindowClose(Events::WindowClose& e);					///< Window Close Event
		bool onWindowMoved(Events::WindowMoved& e);					///< Window Move Event
		bool onWindowLostFocus(Events::WindowLostFocus& e);			///< Window Lost Focus Event
		//Key Events
		bool onKeyPressed(Events::KeyPressed& e);					///< Key Press Event
		bool onKeyReleased(Events::KeyReleased& e);					///< Key Release Event
		bool onKeyTyped(Events::KeyTyped& e);						///< Key Type Event
		//Mouse Events
		bool onMouseMove(Events::MouseMoved& e);					///< Mouse Move Event
		bool onMouseScrolled(Events::MouseScrolled& e);				///< Mouse Scrolled Event
		bool onMouseButtonPressed(Events::MouseButtonPressed& e);	///< Mouse Button Press Event
		bool onMouseButtonReleased(Events::MouseButtonReleased& e);	///< Mouse Button Release Event
	public:
		virtual ~Application(); ///< Deconstructor
		inline static Application& getInstance() { return *s_instance; } ///< Return an Application Pointer
		inline static float getdeltaTime() { return s_deltaTime; } ///< Returns Time Since Last Frame
		inline std::shared_ptr<Window> getWindow() { return m_window; } ///< Returns The Window
		void run(); ///< Update Loop
		void onEvent(Events::Event& e); ///< Called On an Event
	};

	Application* startApplication();

}