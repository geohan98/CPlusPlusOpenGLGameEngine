#pragma once
#include "systems/log.h"
#include "systems/time.h"
#include "windows/windowSystem.h"
#include "windows/window.h"
#include "systems/resourceManager.h"
#include "systems/layerStack.h"

namespace Engine {


	/**
	 *  A test class. A more elaborate class description.
	 */
	class Application
	{
	protected:
		Application();
		std::shared_ptr<Log> m_log;
		std::shared_ptr<Time> m_time;
		std::shared_ptr<WindowSystem> m_windowSystem;
		std::shared_ptr<Window> m_window;
		static std::shared_ptr<ResourceManager> m_resourceManager;
		std::shared_ptr<LayerStack> m_layerStack;
	private:
		static Application* s_instance;
		bool m_running = true;
		static glm::ivec2 s_screenResolution;
		static float s_deltaTime;
		//Window Events
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
		virtual ~Application();
		inline static Application& getInstance() { return *s_instance; }
		inline static float getdeltaTime() { return s_deltaTime; }
		inline std::shared_ptr<Window> getWindow() { return m_window; }
		void run(); //!< Main loop
		void onEvent(Event& e);
	};

	Application* startApplication();

}