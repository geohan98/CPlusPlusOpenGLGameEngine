#include <systems/log.h>

Engine::Log::Log()
{
}

Engine::Log::~Log()
{
}

void Engine::Log::start(SystemSignal init, ...)
{
	if (!b_loggerActive)
	{
		m_logger = spdlog::basic_logger_mt("Basic Logger", "logs/basic.txt");
		b_loggerActive = true;
		m_logger->info("Logger Started");
	}
	else
	{
		m_logger->info("Logger Already Running");
	}
}

void Engine::Log::stop(SystemSignal close, ...)
{
	if (b_loggerActive)
	{
		m_logger->info("Logger Stopping");
	}
}
