#pragma once

#include <systems/system.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace Engine {

	/**
	 * Log, Allows printing to the console
	 */
	class Log : public System
	{
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;											///< logger for the engine
		static std::shared_ptr<spdlog::logger> s_clientLogger;											///< logger for the client/app
		static bool s_loggerActive;																		///< is the logger running
	public:
		void start(SystemSignal init = SystemSignal::None, ...);										///< start the logger
		void stop(SystemSignal close = SystemSignal::None, ...);										///< stop the logger

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; };		///<  return the engine logger
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; };	///< return the client logger
		inline static bool getLoggerStatus() { return s_loggerActive; };								///< return the status of the logger
	};
}

// Core log macros
#define LOG_CORE_TRACE(...)    Log::getCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)     Log::getCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)     Log::getCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)    Log::getCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LOG_TRACE(...)         Engine::Log::getClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          Engine::Log::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          Engine::Log::getClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         Engine::Log::getClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      Engine::Log::getClientLogger()->critical(__VA_ARGS__)