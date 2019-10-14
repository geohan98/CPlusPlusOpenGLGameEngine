#pragma once
#include <systems/system.h>
#include <memory>
#include <chrono>

namespace Engine {
	class Timer
	{
	private:
		static std::shared_ptr <std::chrono::high_resolution_clock::time_point> m_appStart;
		static bool b_timerActive;
	public:
		Timer();
		~Timer();

		void start(SystemSignal init = SystemSignal::None, ...);
		void stop(SystemSignal close = SystemSignal::None, ...);

		inline static std::shared_ptr <std::chrono::high_resolution_clock::time_point> getAppStart() { return m_appStart; };
		inline static bool getTimerStatus() { return b_timerActive; };
	};
}