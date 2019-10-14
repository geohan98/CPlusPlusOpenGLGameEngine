#include "engine_pch.h"
#include "include/independent/systems/timer.h"


namespace Engine {

	std::shared_ptr<std::chrono::high_resolution_clock::time_point> m_appStart;
	bool Timer::b_timerActive = false;

	Timer::Timer()
	{
	}

	Timer::~Timer()
	{
	}

	void Timer::start(SystemSignal init, ...)
	{
		*m_appStart = std::chrono::high_resolution_clock::now();
	}

	void Timer::stop(SystemSignal close, ...)
	{
	}

}
