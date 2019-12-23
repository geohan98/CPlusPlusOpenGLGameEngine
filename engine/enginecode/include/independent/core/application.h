#pragma once
#include "systems/log.h"
#include "systems/time.h"
#include "include/independent/windows/window.h"
#include "windows/window.h"
#include "windows/windowSystem.h"
#include "events/event.h"
#include "events/applicationEvents.h"
#include "events/keyEvents.h"
#include "systems/ButtonCodes.h"
#include "systems/inputPoller.h"
#include "systems/resourceManager.h"
#include "renderer/renderer.h"
#include "core/perspectiveCamera3D.h"

namespace Engine {

	class Application
	{
	protected:
		Application();
	private:
		static Application* s_instance;
		bool m_running = true;
		std::shared_ptr<Window> m_window;
		static glm::ivec2 s_screenResolution;
		std::shared_ptr<Log> m_log;
		std::shared_ptr<Time> m_timer;
		std::shared_ptr<WindowSystem> m_windows;
		std::shared_ptr<ResourceManager> m_resources;
		std::shared_ptr<Renderer> m_renderer;
		std::shared_ptr<PerspectiveCamera3D> m_camera;
		static float s_timestep;
	public:
		virtual ~Application();
		inline static Application& getInstance() { return *s_instance; }
		inline static float getTimestep() { return s_timestep; }
		inline std::shared_ptr<Window> getWindow() { return m_window; }
		void onEvent(Event& e);
		bool onClose(WindowClose& e);
		bool onResize(WindowResize& e);
		bool onKeyPressed(KeyPressed& e);
		void run(); //!< Main loop
	};

	Application* startApplication();

}