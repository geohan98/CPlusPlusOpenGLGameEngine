#pragma once
#include <systems/system.h>
#include <chrono>

namespace Engine
{
	class Time : public System
	{
		static std::chrono::high_resolution_clock::time_point s_appStart;
		static std::chrono::high_resolution_clock::time_point s_frameStart;
		static std::chrono::duration<float> s_deltaTime;
		static float s_timeScale;
		static bool s_timeActive;
	public:
		void start(SystemSignal init = SystemSignal::None, ...);
		void stop(SystemSignal close = SystemSignal::None, ...);

		void reset();
		void tick();

		inline static void setTimeScale(float t) { s_timeScale = t; }
		inline static float getTimeScale() { return s_timeScale; }
		inline static float getDeltaTime() { return s_deltaTime.count(); }
		inline static float getAppStart() { return s_appStart.time_since_epoch().count(); }
		inline static bool getTimerStatus() { return s_timeActive; }
	};
}

//Time macros
#define TIME_DELTA_TIME Time::getDeltaTime()
#define TIME_TIME_SCALE Time::getTimeScale()
#define TIME_APP_START Time::getAppStart()