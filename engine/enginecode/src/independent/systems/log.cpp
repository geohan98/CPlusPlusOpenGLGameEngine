#include "engine_pch.h"
#include "systems/log.h"


namespace Engine {

	//Singleton Pattern
	bool I_Logger::b_Flag = false;
	I_Logger* I_Logger::instance = nullptr;
	I_Logger* I_Logger::getInstance()
	{
		if (!b_Flag)
		{
			instance = new I_Logger();
			b_Flag = true;
			return instance;
		}
		else
		{
			return instance;
		}
	}

	I_Logger::I_Logger() {}

	I_Logger::~I_Logger() {}

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

	void I_Logger::Info(std::string msg)
	{
		m_logger->info(msg);
	}

	void I_Logger::Info(float msg)
	{
		m_logger->info(msg);
	}

	void I_Logger::Warning(std::string msg)
	{
		m_logger->warn(msg);
	}

	void I_Logger::Warning(float msg)
	{
		m_logger->warn(msg);
	}

	void I_Logger::Error(std::string msg)
	{
		m_logger->error(msg);
	}

	void I_Logger::Error(float msg)
	{
		m_logger->error(msg);
	}

	void I_Logger::Critical(std::string msg)
	{
		m_logger->critical(msg);
	}

	void I_Logger::Critical(float msg)
	{
		m_logger->critical(msg);
	}

}