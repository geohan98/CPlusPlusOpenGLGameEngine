#pragma once
#include <systems/system.h>
#include <chrono>

namespace Engine
{
	namespace Systems {
		/**
		 *  Time, Allow time keeping
		 */
		class Time : public System
		{
			static std::chrono::high_resolution_clock::time_point s_appStart;					///< Time point for start of app
			static std::chrono::high_resolution_clock::time_point s_frameStart;					///< Time point for start of frame
			static std::chrono::duration<float> s_deltaTime;									///< Time Since Last Frame
			static float s_timeScale;															///< Time Scale
			static bool s_timeActive;															///< is the timer active
		public:
			void start(SystemSignal init = SystemSignal::None, ...);							///< Start the Time System
			void stop(SystemSignal close = SystemSignal::None, ...);							///< Stop the time System

			void tick();																		///< Update Delta Time

			inline static void setTimeScale(float t) { s_timeScale = t; }						///< Set Time Scale
			inline static float getTimeScale() { return s_timeScale; }							///< Return Time Scale
			inline static float getDeltaTime() { return s_deltaTime.count(); }					///< get Delta Time
			inline static float getAppStart() { return s_appStart.time_since_epoch().count(); }	///< get App Start
			inline static bool getTimerStatus() { return s_timeActive; }						///< return is the timer active
		};
	}
}

//Time macros
#define TIME_DELTA_TIME Systems::Time::getDeltaTime()
#define TIME_TIME_SCALE Systems::Time::getTimeScale()
#define TIME_APP_START Systems::Time::getAppStart()