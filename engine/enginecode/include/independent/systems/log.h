

#include <systems/system.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace Engine {

	class Log : public System
	{
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
		static bool s_loggerActive;
	public:
		void start(SystemSignal init = SystemSignal::None, ...);
		void stop(SystemSignal close = SystemSignal::None, ...);

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; };
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; };
		inline static bool getLoggerStatus() { return s_loggerActive; };
	};
}

// Core log macros
#define LOG_CORE_TRACE(...)    Log::getCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)     Log::getCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)     Log::getCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)    Log::getCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LOG_TRACE(...)         Log::getClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          Log::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          Log::getClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         Log::getClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      Log::getClientLogger()->critical(__VA_ARGS__)