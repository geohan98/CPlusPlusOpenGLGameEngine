#include "engine_pch.h"
#include "systems/log.h"


namespace Engine {

	std::shared_ptr<spdlog::logger> I_Logger::m_logger;
	bool I_Logger::b_loggerActive = false;

	I_Logger::I_Logger()
	{
	}

	I_Logger::~I_Logger()
	{
	}

	void I_Logger::start(SystemSignal init, ...)
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

	void I_Logger::stop(SystemSignal close, ...)
	{
		if (b_loggerActive)
		{
			m_logger->info("Logger Stopping");
		}
	}

}