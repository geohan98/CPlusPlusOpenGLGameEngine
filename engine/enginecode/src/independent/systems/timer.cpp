#include "engine_pch.h"
#include "include/independent/systems/timer.h"


namespace Engine {

	std::chrono::high_resolution_clock::time_point I_Timer::m_appStart;
	bool I_Timer::b_timerActive = false;

	I_Timer::I_Timer() {}

	I_Timer::~I_Timer() {}

	void I_Timer::start(SystemSignal init, ...)
	{
		b_timerActive = true;
		Reset();
		m_timeScale = 1.0f;
		m_DeltaTime = std::chrono::duration<float>(0.0f);
	}

	void I_Timer::stop(SystemSignal close, ...) {}

	void I_Timer::Reset() 
	{
		m_frameStart = std::chrono::high_resolution_clock::now();
	}

	void I_Timer::setTimeScale(float t)
	{
		m_timeScale = t;
	}

	void I_Timer::Tick()
	{
		m_DeltaTime = std::chrono::high_resolution_clock::now() - m_frameStart;
	}

}
