#pragma once
#include <systems/system.h>
#include <memory>
#include <chrono>

namespace Engine
{
	class I_Timer : public System
	{
		//Singleton Pattern
	private:
		static bool b_Flag;
		static I_Timer* instance;
		I_Timer();
	public:
		static I_Timer* getInstance();
		~I_Timer();

	private:
		std::chrono::high_resolution_clock::time_point m_appStart;
		std::chrono::high_resolution_clock::time_point m_frameStart;
		std::chrono::duration<float> m_DeltaTime = std::chrono::duration<float>(0.0f);
		float m_timeScale = 1.0f;
		bool b_timerActive = false;
	public:
		void start(SystemSignal init = SystemSignal::None, ...);
		void stop(SystemSignal close = SystemSignal::None, ...);

		void Reset();
		void Tick();

		inline void setTimeScale(float t) { m_timeScale = t; }
		inline float getTimeScale() { return m_timeScale; }
		inline float getDeltaTime() { return m_DeltaTime.count(); }
		inline float getAppStart() { return m_appStart.time_since_epoch().count(); }
		inline bool getTimerStatus() { return b_timerActive; }
	};
}