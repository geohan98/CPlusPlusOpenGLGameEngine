#pragma once

#include <systems/system.h>
#include <memory>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Engine {

	class I_Logger : public System
	{
	private:
		static std::shared_ptr<spdlog::logger> m_logger;
		static bool b_loggerActive;
	public:
		I_Logger();
		~I_Logger();
		void start(SystemSignal init = SystemSignal::None, ...);
		void stop(SystemSignal close = SystemSignal::None, ...);

		inline static std::shared_ptr<spdlog::logger>& getLogger() { return m_logger; };
		inline static bool getLoggerStatus() { return b_loggerActive; };
	};
}