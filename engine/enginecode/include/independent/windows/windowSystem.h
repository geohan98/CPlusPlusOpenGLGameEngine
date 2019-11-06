#pragma once
#include "systems/system.h"
#include "windows/window.h"

namespace Engine
{
	class WindowSystem : public System
	{
	protected:
		Window* m_window;
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0;
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0;
		void setEventCallback(const std::function<void(Event&)>& callback) { m_window->setEventCallback(callback); };
		void update(float timestep) { m_window->onUpdate(timestep); }
		inline void* getNativeWindow() { return m_window->getNativeWindow(); }
	};
}