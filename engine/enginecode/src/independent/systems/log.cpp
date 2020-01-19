#include "engine_pch.h"
#include "systems/log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{
	namespace Systems {
		std::shared_ptr<spdlog::logger> Log::s_coreLogger;
		std::shared_ptr<spdlog::logger> Log::s_clientLogger;
		bool Log::s_loggerActive = false;

		void Log::start(SystemSignal init, ...)
		{
			spdlog::set_pattern("%^[%T] %n: %v%$");
			s_coreLogger = spdlog::stdout_color_mt("ENGINE");
			s_coreLogger->set_level(spdlog::level::trace);

			s_clientLogger = spdlog::stdout_color_mt("APP");
			s_clientLogger->set_level(spdlog::level::trace);

			s_loggerActive = true;
		}

		void Log::stop(SystemSignal close, ...)
		{
		}

	}
}
