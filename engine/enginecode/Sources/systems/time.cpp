#include "engine_pch.h"
#include "../enginecode/Headers/systems/time.h"
#include "Headers/systems/log.h"

namespace Engine
{
	namespace Systems {
		std::chrono::high_resolution_clock::time_point Time::s_appStart;
		std::chrono::high_resolution_clock::time_point Time::s_frameStart;
		std::chrono::duration<float> Time::s_deltaTime;
		float Time::s_timeScale;
		bool Time::s_timeActive = false;

		void Time::start(SystemSignal init, ...)
		{
			LOG_CORE_WARN("[SYSTEMS][TIME][TIMER STARTED]");
			s_appStart = std::chrono::high_resolution_clock::now();
			s_frameStart = std::chrono::high_resolution_clock::now();
			s_deltaTime = std::chrono::duration<float>(0.0f);
			s_timeScale = 1.0f;
			s_timeActive = true;
		}

		void Time::stop(SystemSignal close, ...)
		{
			LOG_CORE_WARN("[SYSTEMS][TIME][TIMER STOPPED]");
		}

		void Time::tick()
		{
			s_deltaTime = std::chrono::high_resolution_clock::now() - s_frameStart;
			s_frameStart = std::chrono::high_resolution_clock::now();
		}
	}
}