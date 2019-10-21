#pragma once
#include <systems/system.h>
#include <memory>
#include <chrono>

namespace Engine {
	class I_Timer
	{
	private:
		static std::chrono::high_resolution_clock::time_point m_appStart;
		std::chrono::high_resolution_clock::time_point m_frameStart;
		std::chrono::duration<float> m_DeltaTime;
		float m_timeScale;
		static bool b_timerActive;
	public:
		I_Timer();
		~I_Timer();

		void start(SystemSignal init = SystemSignal::None, ...);
		void stop(SystemSignal close = SystemSignal::None, ...);

		void Reset();
		void Tick();

		void setTimeScale(float t = 1.0f);
		float getTimeScale() { return m_timeScale; }
		inline float getDeltaTime() { return m_DeltaTime.count(); }

		static float getAppStart(){ return m_appStart.time_since_epoch().count(); }
		inline static bool getTimerStatus() { return b_timerActive; };
	};
}