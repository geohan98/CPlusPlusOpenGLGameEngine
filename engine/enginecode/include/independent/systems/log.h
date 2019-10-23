#pragma once

#include <systems/system.h>
#include <memory>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Engine {

	class I_Logger : public System
	{
		//Singleton Pattern
	private:
		static bool b_Flag;
		static I_Logger* instance;
		I_Logger();
	public:
		static I_Logger* getInstance();
		~I_Logger();

	private:
		std::shared_ptr<spdlog::logger> m_logger;
		bool b_loggerActive = false;
	public:
		void start(SystemSignal init = SystemSignal::None, ...);
		void stop(SystemSignal close = SystemSignal::None, ...);

		inline std::shared_ptr<spdlog::logger>& getLogger() { return m_logger; };
		inline bool getLoggerStatus() { return b_loggerActive; };

		void Info(std::string msg);
		void Info(float msg);

		void Warning(std::string msg);
		void Warning(float msg);

		void Error(std::string msg);
		void Error(float msg);

		void Critical(std::string msg);
		void Critical(float msg);
	};
}