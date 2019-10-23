#include "engine_pch.h"
#include "include/independent/systems/timer.h"



namespace Engine
{
	//Singleton Pattern
	bool I_Timer::b_Flag = false;
	I_Timer* I_Timer::instance = nullptr;
	I_Timer* I_Timer::getInstance()
	{
		if (!b_Flag)
		{
			instance = new I_Timer();
			b_Flag = true;
			return instance;
		}
		else
		{
			return instance;
		}
	}

	I_Timer::I_Timer() {}

	I_Timer::~I_Timer() {}

	void I_Timer::start(SystemSignal init, ...)
	{
		b_timerActive = true;
		Reset();
		m_timeScale = 1.0f;
		m_DeltaTime = std::chrono::duration<float>(0.0f);
	}

	void I_Timer::stop(SystemSignal close, ...)
	{
	}

	void I_Timer::Reset()
	{
		m_frameStart = std::chrono::high_resolution_clock::now();
	}

	void I_Timer::Tick()
	{
		m_DeltaTime = std::chrono::high_resolution_clock::now() - m_frameStart;
	}

}
