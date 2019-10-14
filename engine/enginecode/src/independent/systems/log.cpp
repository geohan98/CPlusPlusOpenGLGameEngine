#include "engine_pch.h"
#include "systems/log.h"


namespace Engine {

	std::shared_ptr<spdlog::logger> Log::m_logger;
	bool Log::b_loggerActive = false;

	Log::Log()
	{
	}

	Log::~Log()
	{
	}

	void Log::start(SystemSignal init, ...)
	{
		if (!b_loggerActive)
		{
			m_logger = spdlog::stdout_color_st("Console");
			b_loggerActive = true;
			m_logger->info("Logger Started");
		}
		else
		{
			m_logger->info("Logger Already Running");
		}
	}

	void Log::stop(SystemSignal close, ...)
	{
		if (b_loggerActive)
		{
			m_logger->info("Logger Stopping");
		}
	}

}