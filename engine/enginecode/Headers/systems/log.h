#pragma once

#include <../enginecode/Headers/systems/system.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace Engine {
	namespace Systems {
		/**
		 * Log, Allows printing to the console
		 */
		class Log : public System
		{
		private:
			static std::shared_ptr<spdlog::logger> s_coreLogger;											///< logger for the engine
			static std::shared_ptr<spdlog::logger> s_clientLogger;											///< logger for the client/app
		public:
			void start(SystemSignal init = SystemSignal::None, ...);										///< start the logger
			void stop(SystemSignal close = SystemSignal::None, ...);										///< stop the logger

			inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; };		///<  return the engine logger
			inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; };	///< return the client logger
		};

	}
}


// Core log macros
#define LOG_CORE_TRACE(...)    Systems::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)     Systems::Log::getCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)     Systems::Log::getCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)    Systems::Log::getCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) Systems::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LOG_TRACE(...)         Engine::Systems::Log::getClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          Engine::Systems::Log::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          Engine::Systems::Log::getClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         Engine::Systems::Log::getClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      Engine::Systems::Log::getClientLogger()->critical(__VA_ARGS__)